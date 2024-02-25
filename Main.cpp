#include <iostream>
#include "opencv2/core/core.hpp"
#include "opencv2/imgproc/imgproc.hpp"
#include "opencv2/highgui/highgui.hpp"

int threshold;
cv::Mat image;
cv::Mat originalImage;
cv::Mat contourOutput;
cv::Mat contourImage;

int main(int argc, const char * argv[]) {

    image= cv::imread("../sample.jpeg");
	
    if (!image.data) {
        std::cout << "Image file not found\n";
        return 1;
    }
    

	cv::imshow("Threshold Image", image);
	cv::imshow("Output Image", contourImage);
    cv::waitKey(0);

    return 0;
}