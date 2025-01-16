#include "Specification.h"

#include <iostream>

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

std::string Specification::toString() {
    std::string str;

    // Convert shape to Dutch
    switch (shape) {
        case CIRCLE:
            str.append("cirkel");
            break;
        case SEMICIRCLE:
            str.append("halve cirkel");
            break;
        case SQUARE:
            str.append("vierkant");
            break;
        case RECTANGLE:
            str.append("rechthoek");
            break;
        case TRIANGLE:
            str.append("driehoek");
            break;
        default:
            str.append("onbekende vorm");
            break;
    }

    str.append(" "); // Add a space between shape and color

    // Convert color to Dutch
    switch (color) {
        case PINK:
            str.append("roze");
            break;
        case ORANGE:
            str.append("oranje");
            break;
        case YELLOW:
            str.append("geel");
            break;
        case GREEN:
            str.append("groen");
            break;
        default:
            str.append("onbekende kleur");
            break;
    }

    return str;
}
