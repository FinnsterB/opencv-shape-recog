#ifndef SPEC_FINDER_H
#define SPEC_FINDER_H

#include "Specification.h"

#include "opencv2/core/core.hpp"
#include "opencv2/imgproc/imgproc.hpp"

#include <vector>

class SpecFinder
{
private:
    Specification spec;
public:
    SpecFinder(/* args */);
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
    void findSpec(cv::Mat& src, std::vector<std::vector<cv::Point>> contours, std::vector<cv::Vec4i> hierarchy){
        //Filter for color
        
        //Threshold

        //Find contours
        findContours( src, contours, hierarchy, cv::RETR_TREE, cv::CHAIN_APPROX_SIMPLE );

        //Find required shape
    }
};

#endif