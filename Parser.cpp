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
    std::string token;
    std::vector<SpecFinder> specs;

    fileIn.open(file);
    while (!fileIn.eof())
    {
        if(fileIn.peek() == '#'){
            while (fileIn.peek() != '\n')
            {
                fileIn >> garbage;
                garbage = "";
            }   
        }
        fileIn >> token;
        if(token != ""){
            if(token == "cirkel"){
                
            }
        }

    }
    
    
    return std::vector<SpecFinder>();
}
