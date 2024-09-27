#include <iostream>
#include <vector>
#include "opencv2/core/core.hpp"
#include "opencv2/imgproc/imgproc.hpp"
#include "opencv2/highgui/highgui.hpp"

#include "SpecFinder.h"
#include "Parser.h"

int threshold;
cv::Mat image;
cv::Mat originalImage;
cv::Mat contourOutput;
cv::Mat contourImage;
std::vector<SpecFinder> specFinders;
std::vector<std::vector<cv::Point>> contours;
std::vector<cv::Vec4i> hierarchy;

int main(int argc, const char * argv[]) {
    
    cv::VideoCapture cap;
    
    for (int8_t i = 4; i >= 0; i--)
    {
        try
        {
            cap = cv::VideoCapture(i);
        }
        catch(const std::exception& e)
        {
            //std::cerr << e.what() << '\n';
        }
        if(cap.isOpened()){
            std::cout << "Camera gevonden!" << std::endl;
            break;
        }
    }
    
    if(!cap.isOpened()){
        std::cout << "Geen camera gevonden!" << std::endl;
        return 1;
    }
    
	

    
	
    if(argc > 1){
        //Batch mode
        std::string fileName(argv[1]);
        specFinders = Parser::parse(fileName);
        //std::cout << "Parsed specs: " << std::endl;
        for (SpecFinder s : specFinders)
        {
            std::cout << "Shape: " << std::to_string(s.spec.getShape()) << ", Color: " << std::to_string(s.spec.getColor()) << std::endl;
        }
        
    }
    else
    {
        //Interactive mode
    }
    

    while (true)
    {
        cap.read(image);
        originalImage = image.clone();
        contours.clear();
        for (SpecFinder s : specFinders)
        {
            cv::Mat processableImage = image.clone();
            s.findSpec(processableImage, contours, hierarchy);
        }
        cv::drawContours(image, contours, -1, cv::Scalar(255,0,0), 3);
        std::string text = std::to_string(contours.size()) + " contours found";
        cv::putText(image, text, cv::Point2d(20, 20), cv::FONT_HERSHEY_PLAIN, 1,7);
        cv::imshow("Found contours", image);
        char key = cv::waitKey(20);
        if(key == 27){
            break;
        }else if(key == 'c'){
            for (SpecFinder s : specFinders)
            {
                s.startCalibration();
            }
        }
    }
    
    

    return 0;
}
