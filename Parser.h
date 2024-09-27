#ifndef PARSER_H
#define PARSER_H

#include "SpecFinder.h"

#include <vector>
#include <string>


class Parser
{
private:
    static int parseColor(const std::string& token);
    static int parseShape(const std::string &token);

public:
    Parser(/* args */);
    ~Parser();
    static std::vector<SpecFinder> parse(const std::string& file);
    static void parseLine(const std::string& line, std::vector<SpecFinder>& specFinders);
};

#endif