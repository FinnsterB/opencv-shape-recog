#include "termios.h"
#include "unistd.h"
#include "opencv2/core/core.hpp"
#include "opencv2/imgproc/imgproc.hpp"
#include "opencv2/highgui/highgui.hpp"

#include "SpecFinder.h"
#include "Parser.h"

#include <iostream>
#include <vector>
#include <thread>
#include <atomic>
#include <chrono>

#define CLOCKSPD 3.6e9

int threshold;
cv::Mat image;
cv::Mat originalImage;
cv::Mat contourOutput;
cv::Mat contourImage;
std::vector<SpecFinder> specFinders;
std::vector<SpecifiedContour> contours;
std::vector<cv::Vec4i> hierarchy;


// Flag to indicate when to stop input thread
std::atomic<bool> running(true);

// Shared data and synchronization
std::mutex mtx;
std::string sharedInput;
bool inputAvailable = false;

// Function to handle user input in a separate thread
void inputThreadFunction() {
    std::string input;
    while (running) {
        std::getline(std::cin, input);  // Block and wait for user input

        if (!input.empty()) {
            std::lock_guard<std::mutex> lock(mtx);  // Lock mutex to modify shared data
            sharedInput = input;
            inputAvailable = true;

            if (input == "exit") {  // Exit the loop if the user types 'exit'
                running = false;
            }
        }
    }
}


int main(int argc, const char * argv[]) {
    
    cv::VideoCapture cap;
    
    // Trying all possible capture devices until the right one is found.
    // Starts at 4 and counts down to favor external webcams.
    // This makes OpenCV generate warnings, but they can't be turned off.
    for (int8_t i = 4; i >= 0; i--)
    {
        try
        {
            cap = cv::VideoCapture(i);
        }
        catch(const std::exception& e)
        {
            std::cerr << e.what() << '\n';
        }
        if(cap.isOpened()){
            //Camera is found, continue normal flow.
            break;
        }
    }
    
    if(!cap.isOpened()){
        std::cerr << "Geen camera gevonden!" << std::endl;
        return 1;
    }

    if(argc > 1){
        /******BATCH MODE******/

        //Parse file given in argument
        std::string fileName(argv[1]);
        specFinders = Parser::parse(fileName);
        while (true)
        {
            //Read image
            cap.read(image);
            contours.clear();

            //Find specified color and shape
            for (SpecFinder s : specFinders)
            {
                // std::chrono timer
                auto start = std::chrono::high_resolution_clock::now();

                //Finding shape and color
                cv::Mat processableImage = image.clone();
                s.findSpec(processableImage, contours, hierarchy);

                // std::chrono duration calculation
                auto end = std::chrono::high_resolution_clock::now();
                auto duration = std::chrono::duration_cast<std::chrono::nanoseconds>(end - start).count();
                std::cout << "Elapsed time: " << (duration * CLOCKSPD) / 1e9 << " clockcycles" << std::endl;
            }

            //Draw all found contours on image
            //cv::drawContours(image, contours, -1, cv::Scalar(255,0,0), 3);
            std::string text = std::to_string(contours.size()) + " contours found";
            for (SpecifiedContour contour : contours)
            {
                // This is sadly required cause OpenCV isn't very flexible in how it's functions are used.
                std::vector<std::vector<cv::Point>> tempContour;
                tempContour.push_back(contour.contour);
                cv::drawContours(image, tempContour, -1, cv::Scalar(255,0,0), 3);

                cv::Moments moments = cv::moments(contour.contour);

                // Centroid coordinates for drawing
                int cX = static_cast<int>(moments.m10 / moments.m00);
                int cY = static_cast<int>(moments.m01 / moments.m00);

                cv::putText(image, std::string(std::to_string(cX) + ", " + std::to_string(cY)), cv::Point(cX, cY) , cv::FONT_HERSHEY_PLAIN, 1,7);
                cv::drawMarker(image, cv::Point(cX, cY), 1);
            }
            
            cv::putText(image, text, cv::Point2d(20, 20), cv::FONT_HERSHEY_PLAIN, 1,7);
            cv::imshow("Found contours", image);
            char key = cv::waitKey(20);
            if(key == 27)
            {
                break;
            }
            else if(key == 'c')
            {
                for (SpecFinder s : specFinders)
                {
                    s.startCalibration();
                }
            }
        }
    }
    else
    {
        /******INTERACTIVE MODE******/

        // Start input thread
        std::thread inputThread(inputThreadFunction);
        std::cout << "Start typing (press Enter to submit):\n";

        while (true) {
            //Read image
            cap.read(image);
            contours.clear();
            
            //Find specified colors and shapes
            for (SpecFinder s : specFinders)
            {
                cv::Mat processableImage = image.clone();
                s.findSpec(processableImage, contours, hierarchy);
            }
            //Draw found contours on image
            //cv::drawContours(image, contours, -1, cv::Scalar(255,0,0), 3);
            for (SpecifiedContour contour : contours)
            {
                // This is sadly required cause OpenCV isn't very flexible in how it's functions are used.
                std::vector<std::vector<cv::Point>> tempContour;
                tempContour.push_back(contour.contour);
                cv::drawContours(image, tempContour, -1, cv::Scalar(255,0,0), 3);
                cv::Moments moments = cv::moments(contour.contour);

                // Centroid coordinates for drawing
                int cX = static_cast<int>(moments.m10 / moments.m00);
                int cY = static_cast<int>(moments.m01 / moments.m00);

                cv::putText(image, std::string(std::to_string(cX) + ", " + std::to_string(cY)),cv::Point(cX, cY) , cv::FONT_HERSHEY_PLAIN, 1,7);
                cv::drawMarker(image, cv::Point(cX, cY), 1);
            }
            std::string text = std::to_string(contours.size()) + " contours found";
            cv::putText(image, text, cv::Point2d(20, 20), cv::FONT_HERSHEY_PLAIN, 1,7);
            cv::imshow("Found contours", image);

            char key = cv::waitKey(20);
            if(key == 27)
            {
                break;
            }
            // Only works by pressing the 'c' key while having OpenCV window in focus.
            else if(key == 'c')
            {
                for (SpecFinder s : specFinders)
                {
                    s.startCalibration();
                }
            }
            if(inputAvailable){
                Parser::parseLine(sharedInput, specFinders);
            }
        }
        inputThread.join();
    }
    return 0;
}
