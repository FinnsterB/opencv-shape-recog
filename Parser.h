#ifndef PARSER_H
#define PARSER_H

#include "SpecFinder.h"

#include <vector>
#include <string>

/**
 * @brief The Parser can either parse a whole file or a single line.
 */
class Parser
{
private:
    /**
     * @brief This function parses a color token into a color enumeration.
     */
    static int parseColor(const std::string& token);
    /**
     * @brief This function parses a shape token into a shape enumeration.
     */
    static int parseShape(const std::string &token);

public:
    Parser(/* args */);
    ~Parser();
    /**
     * @brief The parse() function parses an entire file of which the path
     * should be given as the 'file' parameter.
     */
    static std::vector<SpecFinder> parse(const std::string& file);
    /**
     * @brief This parseLine() function parses a single specification from a string
     * and appends it to the specFinders vector. It skips duplicate specs. 
     */
    static void parseLine(const std::string& line, std::vector<SpecFinder>& specFinders);
};

#endif