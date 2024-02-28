#ifndef SPECIFICATION_H
#define SPECIFICATION_H

#include "SpecFinder.h"

class Specification
{
private:
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

};

#endif