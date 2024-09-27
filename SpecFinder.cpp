#include "SpecFinder.h"

#include <iostream>

#include "opencv2/highgui/highgui.hpp"

int SpecFinder::greenLow = 52;
int SpecFinder::greenHigh = 80;
int SpecFinder::greenSaturationLow = 50;
int SpecFinder::greenSaturationHigh = 255;
int SpecFinder::greenValueLow = 5;
int SpecFinder::greenValueHigh = 255;

int SpecFinder::pinkLow = 150;
int SpecFinder::pinkHigh = 180;
int SpecFinder::pinkSaturationLow = 50;
int SpecFinder::pinkSaturationHigh = 255;
int SpecFinder::pinkValueLow = 0;
int SpecFinder::pinkValueHigh = 255;

int SpecFinder::yellowLow = 30;
int SpecFinder::yellowHigh = 45;
int SpecFinder::yellowSaturationLow = 50;
int SpecFinder::yellowSaturationHigh = 255;
int SpecFinder::yellowValueLow = 50;
int SpecFinder::yellowValueHigh = 255;

int SpecFinder::orangeLow = 0;
int SpecFinder::orangeHigh = 25;
int SpecFinder::orangeSaturationLow = 50;
int SpecFinder::orangeSaturationHigh = 255;
int SpecFinder::orangeValueLow = 5;
int SpecFinder::orangeValueHigh = 255;

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
}

/**
 *@brief Finds all shapes according to the specification of this SpecFinder instance
*/
void SpecFinder::findSpec(cv::Mat src, std::vector<std::vector<cv::Point>>& contours, std::vector<cv::Vec4i> hierarchy)
{
    cv::cvtColor(src, src, cv::COLOR_BGR2HSV);

    //Blur image for clarity
    cv::GaussianBlur(src, src, cv::Size(11, 11), 0);

    //Filter for color
    switch (spec.getColor())
    {
    case YELLOW:
        cv::inRange(src, cv::Scalar(yellowLow, yellowSaturationLow, yellowValueLow), cv::Scalar(yellowHigh, yellowSaturationHigh, yellowValueHigh), src);
        cv::imshow("Filtered image yellow", src);
        break;
    case GREEN:
        cv::inRange(src, cv::Scalar(greenLow, greenSaturationLow, greenValueLow), cv::Scalar(greenHigh, greenSaturationHigh, greenValueHigh), src);
        cv::imshow("Filtered image green", src);
        break;
    case PINK:
        cv::inRange(src, cv::Scalar(pinkLow, pinkSaturationLow, pinkValueLow), cv::Scalar(pinkHigh, pinkSaturationHigh, pinkValueHigh), src);
        cv::imshow("Filtered image pink", src);
        break;
    case ORANGE:
        cv::inRange(src, cv::Scalar(orangeLow, orangeSaturationLow, orangeValueLow), cv::Scalar(orangeHigh, pinkSaturationHigh, pinkValueHigh), src);
        cv::imshow("Filtered image orange", src);
        break;
    default:
        break;
    }

    cv::Mat dilationMat(5,5,src.type(),255);

    //Find contours
    std::vector<std::vector<cv::Point>> allContours;

    findContours( src, allContours, hierarchy, cv::RETR_EXTERNAL, cv::CHAIN_APPROX_SIMPLE );
    //std::cout << "Total contours: " << std::to_string(allContours.size()) << std::endl;

    //Find required shape
    switch (spec.getShape())
    {
    case TRIANGLE:
        for (std::vector<cv::Point> contour : allContours)
        {
            //Discard all open contours and small contours
            if(cv::arcLength(contour, true) < 100){
                continue;
            }
            std::vector<cv::Point> approx;
            double epsilon = 0.02 * cv::arcLength(contour, true); // Contour approximation accuracy
            cv::approxPolyDP(contour, approx, epsilon, true);
            // Check if the polygon has 3 vertices
            if (approx.size() == 3) {
                contours.push_back(contour);
            }
        }
        break;
    case SQUARE:
        for (std::vector<cv::Point> contour : allContours)
        {
            //Discard all open contours and small contours
            if(cv::arcLength(contour, true) < 100)
            {
                continue;
            }
            std::vector<cv::Point> approx;
            double epsilon = 0.02 * cv::arcLength(contour, true); // Contour approximation accuracy
            cv::approxPolyDP(contour, approx, epsilon, true);

            // Check if the polygon has 4 vertices
            if (approx.size() == 4) 
            {
                // Calculate the cosine of angles between the edges
                bool isRectangle = true;
                for (int j = 0; j < 4; j++) 
                {
                    cv::Point v1 = approx[j] - approx[(j + 1) % 4];
                    cv::Point v2 = approx[(j + 2) % 4] - approx[(j + 1) % 4];
                    double cosine = std::abs(v1.dot(v2) / (cv::norm(v1) * cv::norm(v2)));
                    
                    // A cosine close to 0 implies a right angle (90 degrees)
                    if (cosine > 0.5) 
                    { // Adjust threshold as needed
                        isRectangle = false;
                        break;
                    }
                }

                if (isRectangle) {
                    //Calculate side length a
                    int dXa = abs(approx.at(0).x - approx.at(1).x);
                    int dYa = abs(approx.at(0).y - approx.at(1).y);
                    int aLength = sqrt(pow(dXa,2)+pow(dYa,2)); //Pythagorean theorem
                    
                    //Calculate side length b
                    int dXb = abs(approx.at(1).x - approx.at(2).x);
                    int dYb = abs(approx.at(1).y - approx.at(2).y);
                    int bLength = sqrt(pow(dXb,2)+pow(dYb,2)); //Pythagorean theorem

                    float errorMargin = 1.2;
                    //Check if sides are equal within margin epsilon
                    if(aLength > bLength/errorMargin && aLength < bLength*errorMargin){
                        std::cout << "Square found with aLength: " << aLength << " and bLength: " << bLength << std::endl;
                        contours.push_back(contour);
                    }
                }
            }
        }
        
        break;
    case RECTANGLE:
        for (std::vector<cv::Point> contour : allContours)
        {
            //Discard all open contours and small contours
            if(cv::arcLength(contour, true) < 100){
                continue;
            }
            std::vector<cv::Point> approx;
            double epsilon = 0.02 * cv::arcLength(contour, true); // Contour approximation accuracy
            cv::approxPolyDP(contour, approx, epsilon, true);
            //std::cout << "Poly size: " << approx.size() << std::endl;
            // Check if the polygon has 4 vertices
            if (approx.size() == 4) {
                // Calculate the cosine of angles between the edges
                bool isRectangle = true;
                for (int j = 0; j < 4; j++) {
                    cv::Point v1 = approx[j] - approx[(j + 1) % 4];
                    cv::Point v2 = approx[(j + 2) % 4] - approx[(j + 1) % 4];
                    double cosine = std::abs(v1.dot(v2) / (cv::norm(v1) * cv::norm(v2)));
                    
                    // A cosine close to 0 implies a right angle (90 degrees)
                    if (cosine > 0.5) { // Adjust threshold as needed
                        isRectangle = false;
                        break;
                    }
                }

                if (isRectangle) {
                    //Calculate side length a
                    int dXa = abs(approx.at(0).x - approx.at(1).x);
                    int dYa = abs(approx.at(0).y - approx.at(1).y);
                    int aLength = sqrt(pow(dXa,2)+pow(dYa,2)); //Pythagorean theorem

                    //Calculate side length b
                    int dXb = abs(approx.at(1).x - approx.at(2).x);
                    int dYb = abs(approx.at(1).y - approx.at(2).y);
                    int bLength = sqrt(pow(dXb,2)+pow(dYb,2)); //Pythagorean theorem

                    float errorMargin = 1.2;
                    //Check if sides are not equal within margin epsilon
                    if(!(aLength > bLength/errorMargin && aLength < bLength*errorMargin)){
                        std::cout << "Rectangle found with aLength: " << aLength << " and bLength: " << bLength << std::endl;
                        contours.push_back(contour);
                    }
                }
            }
        }
        
        break;
    case CIRCLE:
        
        for (std::vector<cv::Point> contour : allContours)
        {
            //Discard all open contours and small contours
            if(cv::arcLength(contour, true) < 100){
                continue;
            }
            //Get area and perimeter
            double area = cv::contourArea(contour);
            double perimeter = cv::arcLength(contour, true);

            // Compute circularity: 4 * PI * Area / Perimeter^2
            double circularity = 4 * 3.1415 * area / (perimeter * perimeter);

            //Circularity should be close to 1
            if(circularity > 0.8 && circularity <= 1.2){
                contours.push_back(contour);
            }
        }
        
        break;
    
    default:
        break;
    }

}
