#ifndef SPEC_FINDER_H
#define SPEC_FINDER_H

#include "Specification.h"

#include "opencv2/core/core.hpp"
#include "opencv2/imgproc/imgproc.hpp"

#include <vector>

class SpecFinder
{
private:
    
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

    void findSpec(cv::Mat& src, std::vector<std::vector<cv::Point>> contours, std::vector<cv::Vec4i> hierarchy);
};

#endif