#ifndef SPEC_FINDER_H
#define SPEC_FINDER_H


class SpecFinder
{
private:
    /* data */
public:
    SpecFinder(/* args */);
    ~SpecFinder();
    enum ColorSpecs{
        PINK,
        ORANGE,
        YELLOW,
        GREEN
    };
    enum ShapeSpecs{
        CIRCLE,
        SEMICIRCLE,
        SQUARE,
        RECTANGLE,
        TRIANGLE
    };
};

#endif