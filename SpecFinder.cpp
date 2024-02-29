#include "SpecFinder.h"

SpecFinder::SpecFinder(/* args */)
{
}

SpecFinder::SpecFinder(Specification& s): spec(s)
{
}

SpecFinder::~SpecFinder()
{
}

void SpecFinder::findSpec(cv::Mat &src, std::vector<std::vector<cv::Point>> contours, std::vector<cv::Vec4i> hierarchy)
{
        //Filter for color
        
        //Threshold

        //Find contours
        findContours( src, contours, hierarchy, cv::RETR_TREE, cv::CHAIN_APPROX_SIMPLE );

        //Find required shape
}
