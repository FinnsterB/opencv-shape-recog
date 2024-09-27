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

/*static*/ void SpecFinder::startCalibration()
{
    std::string winNameGreen = "CalibrationGreen";
    cv::namedWindow(winNameGreen);

    //Inputs for green HSV
    cv::createTrackbar("Green lower hue", winNameGreen, &greenLow, 180);
    cv::createTrackbar("Green upper hue", winNameGreen, &greenHigh, 180);
    cv::createTrackbar("Green lower saturation", winNameGreen, &greenSaturationLow, 255);
    cv::createTrackbar("Green upper saturation", winNameGreen, &greenSaturationHigh, 255);
    cv::createTrackbar("Green lower value", winNameGreen, &greenValueLow, 255);
    cv::createTrackbar("Green upper value", winNameGreen, &greenValueHigh, 255);

    std::string winNamePink = "CalibrationPink";
    cv::namedWindow(winNamePink);
    
    //Inputs for pink HSV
    cv::createTrackbar("Pink lower hue", winNamePink, &pinkLow, 180);
    cv::createTrackbar("Pink upper hue", winNamePink, &pinkHigh, 180);
    cv::createTrackbar("Pink lower saturation", winNamePink, &pinkSaturationLow, 255);
    cv::createTrackbar("Pink upper saturation", winNamePink, &pinkSaturationHigh, 255);
    cv::createTrackbar("Pink lower value", winNamePink, &pinkValueLow, 255);
    cv::createTrackbar("Pink upper value", winNamePink, &pinkValueHigh, 255);

    std::string winNameYellow = "CalibrationYellow";
    cv::namedWindow(winNameYellow);
    
    //Inputs for Yellow HSV
    cv::createTrackbar("Yellow lower hue", winNameYellow, &yellowLow, 180);
    cv::createTrackbar("Yellow upper hue", winNameYellow, &yellowHigh, 180);
    cv::createTrackbar("Yellow lower saturation", winNameYellow, &yellowSaturationLow, 255);
    cv::createTrackbar("Yellow upper saturation", winNameYellow, &yellowSaturationHigh, 255);
    cv::createTrackbar("Yellow lower value", winNameYellow, &yellowValueLow, 255);
    cv::createTrackbar("Yellow upper value", winNameYellow, &yellowValueHigh, 255);

    std::string winNameOrange = "CalibrationOrange";
    cv::namedWindow(winNameOrange);
    
    //Inputs for pink HSV
    cv::createTrackbar("Orange lower hue", winNameOrange, &orangeLow, 180);
    cv::createTrackbar("Orange upper hue", winNameOrange, &orangeHigh, 180);
    cv::createTrackbar("Orange lower saturation", winNameOrange, &orangeSaturationLow, 255);
    cv::createTrackbar("Orange upper saturation", winNameOrange, &orangeSaturationHigh, 255);
    cv::createTrackbar("Orange lower value", winNameOrange, &orangeValueLow, 255);
    cv::createTrackbar("Orange upper value", winNameOrange, &orangeValueHigh, 255);
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

    //cv::Mat dilationMat(5,5,src.type(),255);

    //Find contours
    std::vector<std::vector<cv::Point>> allContours;

    findContours( src, allContours, hierarchy, cv::RETR_EXTERNAL, cv::CHAIN_APPROX_SIMPLE );
    //std::cout << "Total contours: " << std::to_string(allContours.size()) << std::endl;

    //Call required shape function for this 
    switch (spec.getShape())
    {
    case TRIANGLE:
        for (std::vector<cv::Point> contour : allContours)
        {
            //Discard all open contours and small contours
            if(cv::arcLength(contour, true) < 100){
                continue;
            }
            if (findTriangle(contour))
            {
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
            if (findSquare(contour))
            {
                contours.push_back(contour);
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
            if (findRectangle(contour))
            {
                contours.push_back(contour);
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
            if (findCircle(contour))
            {
                contours.push_back(contour);
            }   
        }
        
        break;
    case SEMICIRCLE:
        for (std::vector<cv::Point> contour : allContours)
        {
            //Discard all open contours and small contours
            if(cv::arcLength(contour, true) < 100){
                continue;
            }
            if(findSemicircle(contour)){
                contours.push_back(contour);
            }
        }
        
        break;
    default:
        break;
    }

}

bool SpecFinder::findRectangle(std::vector<cv::Point>& contour)
{
    std::vector<cv::Point> approx;
    double epsilon = 0.02 * cv::arcLength(contour, true); // Contour approximation accuracy
    cv::approxPolyDP(contour, approx, epsilon, true);
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
                //std::cout << "Rectangle found with aLength: " << aLength << " and bLength: " << bLength << std::endl;
                return true;
            }
        }
    }
    return false;
}

bool SpecFinder::findSquare(std::vector<cv::Point>& contour)
{
    //Approximate the contour to simplify it
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
                //std::cout << "Square found with aLength: " << aLength << " and bLength: " << bLength << std::endl;
                return true;
            }
        }
    }
    return false;
}

bool SpecFinder::findTriangle(std::vector<cv::Point>& contour)
{
    std::vector<cv::Point> approx;
    double epsilon = 0.02 * cv::arcLength(contour, true); // Contour approximation accuracy
    cv::approxPolyDP(contour, approx, epsilon, true);
    // Check if the polygon has 3 vertices
    if (approx.size() == 3) {
        return true;
    }
    return false;
}

bool SpecFinder::findSemicircle(std::vector<cv::Point>& contour)
{

    // Approximate the contour to reduce noise
    std::vector<cv::Point> approx;
    double epsilon = 0.02 * cv::arcLength(contour, true);  // Approximation accuracy
    cv::approxPolyDP(contour, approx, epsilon, true);

    // Fit a minimum enclosing circle
    cv::Point2f center;
    float radius;
    cv::minEnclosingCircle(contour, center, radius);

    // Calculate contour area and circularity
    double contourArea = cv::contourArea(contour);
    double circleArea = 3.1415 * radius * radius;
    double circularity = contourArea / circleArea;


    //Circularity should be close to 0.5 for a semicircle
    if(circularity > 0.4 && circularity <= 0.6){
        //Check for the long line in the contour
        // Analyze the symmetry: Check the number of points forming the arc (more on one side)
        int arcPoints = 0, straightPoints = 0;

        // We assume that points near the diameter will be horizontally aligned
        float errorMargin = 0.1;
        for (size_t j = 0; j < contour.size(); j++) {
            if (std::abs(contour.at(j).y - center.y) < radius * errorMargin) {
                straightPoints++;
            } else {
                arcPoints++;
            }
        }

        // Check if there are significantly more arc points than straight points
        if (arcPoints > straightPoints) {
            // Likely a semi-circle
            //Check if there's no sneaky rectangle
            if (!findRectangle(contour))
            {
                return true;
            }
        }
    }
    return false;
}

bool SpecFinder::findCircle(std::vector<cv::Point>& contour)
{
    //Get area and perimeter
    double area = cv::contourArea(contour);
    double perimeter = cv::arcLength(contour, true);

    // Compute circularity: 4 * PI * Area / Perimeter^2
    double circularity = 4 * 3.1415 * area / (perimeter * perimeter);

    //Circularity should be close to 1
    if(circularity > 0.8 && circularity <= 1.2){
        return true;
    }
    return false;
}
