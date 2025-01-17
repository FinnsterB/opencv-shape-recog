#ifndef SPEC_FINDER_H
#define SPEC_FINDER_H

#include "Specification.h"

#include "opencv2/core/core.hpp"
#include "opencv2/imgproc/imgproc.hpp"

#include <vector>

/**
 * @brief The specifiedContour struct just adds a specification so we can remember what shape
 * the contour is in the main program.
 */
class SpecifiedContour{
public:
    SpecifiedContour() = default;
    SpecifiedContour(const std::vector<cv::Point>&, Specification aSpec);
    std::vector<cv::Point> contour;
    Specification spec;
};

/**
 * @brief The specFinder class finds the shape according to the specification stored in the spec variable.
 * The main.cpp file holds a vector of SpecFinders and executes SpecFinder::findSpec() for each SpecFinder.
 */
class SpecFinder
{
private:
    /**
     * @brief HSV values for every color. They can be calibrated by pressing C on a openCV window.
     */
    static int greenLow;
    static int greenHigh;
    static int greenSaturationLow;
    static int greenSaturationHigh;
    static int greenValueLow;
    static int greenValueHigh;

    static int pinkLow;
    static int pinkHigh;
    static int pinkSaturationLow;
    static int pinkSaturationHigh;
    static int pinkValueLow;
    static int pinkValueHigh;

    static int yellowLow;
    static int yellowHigh;
    static int yellowSaturationLow;
    static int yellowSaturationHigh;
    static int yellowValueLow;
    static int yellowValueHigh;

    static int orangeLow;
    static int orangeHigh;
    static int orangeSaturationLow;
    static int orangeSaturationHigh;
    static int orangeValueLow;
    static int orangeValueHigh;

public:
    SpecFinder();
    explicit SpecFinder(Specification& s);
    ~SpecFinder();


    /**
     * @brief Specification this specFinder will use to find the shape.
     */
    Specification spec;

    /**
     * @brief Shows the calibration windows with the sliders.
     */
    static void startCalibration();

    /**
     * @brief Filters the image according to the required color, finds every contour
     * and processes that contour with one of the find[Shape] functions below.
     */
    void findSpec(cv::Mat src, std::vector<SpecifiedContour>& contours, std::vector<cv::Vec4i> hierarchy);

    /**
     * @brief Returns true if the provided contour is a rectangle. This is determined
     * by checking if the side lengths are not similar and if the corner angles are 
     * ~90 degrees.
     */
    bool findRectangle(std::vector<cv::Point>& contour);
    /**
     * @brief Returns true if the provided contour is a square. This is determined by
     * checking if the side lengths are similar and if the corner angles are ~90 degrees.
     * 
     */
    bool findSquare(std::vector<cv::Point>& contour);
    /**
     * @brief Returns true if the provided contour is a triangle. This is determined by
     * checking if the contour has 3 points.
     */
    bool findTriangle(std::vector<cv::Point>& contour);
    /**
     * @brief Returns true if the provided contour is a circle. This is determined by
     * checking if the circularity is close to 1 with the following roundness equation:
     * 4 * PI * Area / Perimeter^2.
     */
    bool findCircle(std::vector<cv::Point>& contour);
    /**
     * @brief Returns true if the provided contour is a semicircle. This is determined by
     * checking if the circularity is close to 0.5, and if the contour points get closer
     * the center of an approximated circle.
     */
    bool findSemicircle(std::vector<cv::Point>& contour);
};

#endif