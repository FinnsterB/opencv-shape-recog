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
    
	cv::VideoCapture cap(2);

    if(!cap.isOpened()){
        std::cout << "Geen camera gevonden" << std::endl;
        return -1;
    }
	
    if(argc > 1){
        //Batch mode
        std::string fileName(argv[1]);
        specFinders = Parser::parse(fileName);
        //std::cout << "Parsed specs: " << std::endl;
        for (SpecFinder s : specFinders)
        {
            //std::cout << "Shape: " << std::to_string(s.spec.getShape()) << ", Color: " << std::to_string(s.spec.getColor()) << std::endl;
        }
        
    }
    else
    {
        //Interactive mode
    }
    

    while (true)
    {
        cap.read(image);
        cv::imshow("Threshold Image", image);
        for (SpecFinder s : specFinders)
        {
            s.findSpec(image, contours, hierarchy);
        }
        
	    //cv::imshow("Output Image", contourImage);
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
