#ifndef PARSER_H
#define PARSER_H

#include "SpecFinder.h"

#include <vector>
#include <string>


class Parser
{
private:
    static int parseColor(std::string& token);
    static int parseShape(std::string &token);

public:
    Parser(/* args */);
    ~Parser();
    static std::vector<SpecFinder> parse(const std::string& file);
};

#endif