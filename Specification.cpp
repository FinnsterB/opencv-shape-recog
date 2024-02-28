#include "Specification.h"

Specification::Specification(/* args */)
{
}

Specification::Specification(int aShape, int aColor): shape(aShape), color(aColor)
{
}

Specification::~Specification()
{
}

int Specification::getShape()
{
    return shape;
}

int Specification::getColor()
{
    return color;
}

void Specification::setShape(int s)
{
    shape = s;
}

void Specification::setColor(int c)
{
    color = c;
}
