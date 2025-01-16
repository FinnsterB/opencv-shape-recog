#ifndef SPECIFICATION_H
#define SPECIFICATION_H

#include <iostream>

/**
 * @brief All required colors
 */
enum ColorSpecs{
    UNKNOWN_COLOR,
    PINK,
    ORANGE,
    YELLOW,
    GREEN
};
/**
 * @brief All required shapes
 */
enum ShapeSpecs{
    UNKNOWN_SHAPE,
    CIRCLE,
    SEMICIRCLE,
    SQUARE,
    RECTANGLE,
    TRIANGLE
};

/**
 * @brief This class just contains enumerates for a shape and color by which the specfinder will find them.
 */
class Specification
{
private:
    /**
     * @brief These use the enumerates for shapes and colors given in SpecFinder.h
     */
    int shape;
    int color;
public:
    Specification();
    Specification(int s, int c);
    ~Specification();

    int getShape();
    int getColor();
    
    void setShape(int s);
    void setColor(int c);

    std::string toString();

};

#endif