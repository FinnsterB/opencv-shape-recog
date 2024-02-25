#include "Parser.h"

#include <fstream>

Parser::Parser(/* args */)
{
}

Parser::~Parser()
{
}

std::vector<SpecFinder> Parser::parse(const std::string &file)
{
    std::ifstream fileIn;
    std::string garbage;

    fileIn.open(file);
    if(fileIn.peek() == '#'){
        while (fileIn.peek() != '\n')
        {
            fileIn >> garbage;
        }
        
    }
    return std::vector<SpecFinder>();
}
