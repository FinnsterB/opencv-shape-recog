#include "SpecFinder.h"

#include "opencv2/highgui/highgui.hpp"

int SpecFinder::greenLow = 75/2;
int SpecFinder::greenHigh = 150/2;

int SpecFinder::pinkLow = 290/2;
int SpecFinder::pinkHigh = 330/2;

int SpecFinder::yellowLow = 50/2;
int SpecFinder::yellowHigh = 70/2;

int SpecFinder::orangeLow = 10/2;
int SpecFinder::orangeHigh = 40/2;

int SpecFinder::saturationLow = 50;
int SpecFinder::saturationHigh = 200;

int SpecFinder::valueLow = 50;
int SpecFinder::valueHigh = 200;

SpecFinder::SpecFinder(/* args */)
{
}

SpecFinder::SpecFinder(Specification& s): spec(s)
{
}

SpecFinder::~SpecFinder()
{
}

void SpecFinder::startCalibration()
{
    cv::createTrackbar("SatLow", "Threshold Image", nullptr, 255, saturationLowSlider);
    cv::createTrackbar("SatHigh", "Threshold Image", nullptr, 255, saturationHighSlider);
    cv::createTrackbar("ValLow", "Threshold Image", nullptr, 255, valueLowSlider);
    cv::createTrackbar("ValHigh", "Threshold Image", nullptr, 255, valueHighSlider);
}

/**
 *@brief Finds all shapes according to the specification of this SpecFinder instance
*/
void SpecFinder::findSpec(cv::Mat src, std::vector<std::vector<cv::Point>> contours, std::vector<cv::Vec4i> hierarchy)
{
    cv::cvtColor(src, src, cv::COLOR_BGR2HSV);

    //Blur image for clarity
    cv::GaussianBlur(src, src, cv::Size(7,7), 1);

    //Filter for color
    switch (spec.getColor())
    {
    case YELLOW:
        cv::inRange(src, cv::Scalar(yellowLow, saturationLow, valueLow), cv::Scalar(yellowHigh, saturationHigh, valueHigh), src);
        break;
    case GREEN:
        cv::inRange(src, cv::Scalar(greenLow, saturationLow, valueLow), cv::Scalar(greenHigh, saturationHigh, valueHigh), src);
        break;
    case PINK:
        cv::inRange(src, cv::Scalar(pinkLow, saturationLow, valueLow), cv::Scalar(pinkHigh, saturationHigh, valueHigh), src);
        break;
    case ORANGE:
        cv::inRange(src, cv::Scalar(orangeLow, saturationLow, valueLow), cv::Scalar(orangeHigh, saturationHigh, valueHigh), src);
        break;
    default:
        break;
    }

    cv::Mat dilationMat(5,5,src.type(),255);
    cv::erode(src, src, dilationMat);

    cv::dilate(src, src, dilationMat);

    cv::imshow("Filtered image", src);

    cv::Canny(src,src, 100,100);

    //Find contours
    std::vector<std::vector<cv::Point>> allContours;

    findContours( src, allContours, hierarchy, cv::RETR_TREE, cv::CHAIN_APPROX_SIMPLE );

    //Find required shape
    switch (spec.getShape())
    {
    case SQUARE:
        for (std::vector<cv::Point> contour : allContours)
        {
            if(contour.size() == 4 && cv::arcLength(contour, true) > 500){
                //detect square better
                contours.push_back(contour);
            }
        }
        
        break;
    case RECTANGLE:
        for (std::vector<cv::Point> contour : allContours)
        {
            if(contour.size() == 4 && cv::arcLength(contour, true) > 500){
                //detect square better
                contours.push_back(contour);
            }
        }
        
        break;
    case TRIANGLE:
        for (std::vector<cv::Point> contour : allContours)
        {
            if(contour.size() == 3 && cv::arcLength(contour, true) > 500){
                //detect square better
                contours.push_back(contour);
            }
        }
        
        break;
    case CIRCLE:
        for (std::vector<cv::Point> contour : allContours)
        {
            if(contour.size() > 6 && cv::arcLength(contour, true) > 500){
                //detect square better
                contours.push_back(contour);
            }
        }
        
        break;
    
    default:
        break;
    }

}
