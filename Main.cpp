#include <iostream>
#include "opencv2/core/core.hpp"
#include "opencv2/imgproc/imgproc.hpp"
#include "opencv2/highgui/highgui.hpp"

int threshold;
cv::Mat image;
cv::Mat originalImage;
cv::Mat contourOutput;
cv::Mat contourImage;

void thresholdOnChange(int aThreshold, void* userData){
	
	cv::imshow("Threshold Image", image);
	cv::imshow("Output Image", contourImage);

	threshold = aThreshold;

	//Prepare the image for findContours
	cv::blur(image, image, cv::Size(5,5), cv::Point(2,3), cv::BORDER_REFLECT);
    cv::cvtColor(image, image, cv::COLOR_BGR2GRAY);
    cv::threshold(image, image, threshold, 255, 1);

    //Find the contours. Use the contourOutput Mat so the original image doesn't get overwritten
    std::vector<std::vector<cv::Point> > contours;
    contourOutput = image.clone();
    cv::findContours( contourOutput, contours, cv::RETR_LIST, cv::CHAIN_APPROX_NONE );

    //Draw the contours
    cv::Scalar colors[3];
    colors[0] = cv::Scalar(255, 0, 0);
    colors[1] = cv::Scalar(0, 255, 0);
    colors[2] = cv::Scalar(0, 0, 255);
    for (size_t idx = 0; idx < contours.size(); idx++) {
        cv::drawContours(contourImage, contours, idx, colors[idx % 3]);
    }
}

int main(int argc, const char * argv[]) {

    image= cv::imread("../sample.jpeg");
	
    if (!image.data) {
        std::cout << "Image file not found\n";
        return 1;
    }

	cv::Mat originalImage = image.clone();

    //Prepare the image for findContours
	cv::blur(image, image, cv::Size(5,5), cv::Point(2,3), cv::BORDER_REFLECT);
    cv::cvtColor(image, image, cv::COLOR_BGR2GRAY);
    cv::threshold(image, image, 25, 255, 1);

    //Find the contours. Use the contourOutput Mat so the original image doesn't get overwritten
    std::vector<std::vector<cv::Point> > contours;
    contourOutput = image.clone();
    cv::findContours( contourOutput, contours, cv::RETR_LIST, cv::CHAIN_APPROX_NONE );

    //Draw the contours
    contourImage = cv::Mat(image.size(), CV_8UC3, cv::Scalar(0,0,0));
    cv::Scalar colors[3];
    colors[0] = cv::Scalar(255, 0, 0);
    colors[1] = cv::Scalar(0, 255, 0);
    colors[2] = cv::Scalar(0, 0, 255);
    for (size_t idx = 0; idx < contours.size(); idx++) {
        cv::drawContours(contourImage, contours, idx, colors[idx % 3]);
    }
	std::cout << contours.size() << " shapes found!!!" << std::endl;
    cv::imshow("Input Image", originalImage);
	cv::createTrackbar("Threshold", "Input Image", nullptr, 100, thresholdOnChange);

	cv::imshow("Threshold Image", image);
	cv::imshow("Output Image", contourImage);
    cv::waitKey(0);

    return 0;
}