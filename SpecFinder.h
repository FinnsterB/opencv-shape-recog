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

    static int pinkLow;
    static int pinkHigh;

    static int yellowLow;
    static int yellowHigh;

    static int orangeLow;
    static int orangeHigh;

    static int saturationLow;
    static int saturationHigh;

    static int valueLow;
    static int valueHigh;

    static void saturationLowSlider(int value, void* userdata){
        saturationLow = value;
    }
    static void saturationHighSlider(int value, void* userdata){
        saturationHigh = value;
    }

    static void valueLowSlider(int value, void* userdata){
        valueLow = value;
    }
    static void valueHighSlider(int value, void* userdata){
        valueHigh = value;
    }
    

public:
    SpecFinder();
    SpecFinder(Specification& s);
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

    void findSpec(cv::Mat src, std::vector<std::vector<cv::Point>> contours, std::vector<cv::Vec4i> hierarchy);
};

#endif