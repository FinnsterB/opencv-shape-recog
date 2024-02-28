#include <iostream>
#include "opencv2/core/core.hpp"
#include "opencv2/imgproc/imgproc.hpp"
#include "opencv2/highgui/highgui.hpp"

#include "SpecFinder.h"

int threshold;
cv::Mat image;
cv::Mat originalImage;
cv::Mat contourOutput;
cv::Mat contourImage;

int main(int argc, const char * argv[]) {
    
	cv::VideoCapture cap(0);

    if(!cap.isOpened()){
        std::cout << "Geen camera gevonden" << std::endl;
        return -1;
    }
	
    while (true)
    {
        cap.read(image);
        cv::imshow("Threshold Image", image);
	    //cv::imshow("Output Image", contourImage);

        if(cv::waitKey(30) == 27){
            break;
        }
    
    }
    
    

    return 0;
}
