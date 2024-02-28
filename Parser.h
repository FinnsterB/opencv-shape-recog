#ifndef PARSER_H
#define PARSER_H

#include "SpecFinder.h"

#include <vector>
#include <string>


class Parser
{
private:
    SpecFinder::ColorSpecs parseColor(std::string& token);
public:
    Parser(/* args */);
    ~Parser();
    std::vector<SpecFinder> parse(const std::string& file);
};

#endif