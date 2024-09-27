#ifndef SPEC_FINDER_H
#define SPEC_FINDER_H

#include "Specification.h"

#include "opencv2/core/core.hpp"
#include "opencv2/imgproc/imgproc.hpp"

#include <vector>

class SpecFinder
{
private:
    //Hue values for finding:
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
    enum ColorSpecs{
        UNKNOWN_COLOR,
        PINK,
        ORANGE,
        YELLOW,
        GREEN
    };
    enum ShapeSpecs{
        UNKNOWN_SHAPE,
        CIRCLE,
        SEMICIRCLE,
        SQUARE,
        RECTANGLE,
        TRIANGLE
    };

    Specification spec;

    void startCalibration();

    void findSpec(cv::Mat src, std::vector<std::vector<cv::Point>>& contours, std::vector<cv::Vec4i> hierarchy);
};

#endif