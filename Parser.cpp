#include "Parser.h"

#include <fstream>
#include <iostream>

Parser::Parser(/* args */)
{
}

Parser::~Parser()
{
}

/*static*/ std::vector<SpecFinder> Parser::parse(const std::string &file)
{
    std::ifstream fileIn;
    std::string garbage;
    std::string token;
    std::vector<SpecFinder> specFinders;
    int lineNr = 1;

    fileIn.open(file);
    while (!fileIn.eof())
    {
        

        fileIn >> token;
        
        //Check if line is a comment and skip it if it is
        if(token != "" && token.at(0) == '#'){
            while (fileIn.peek() != '\n')
            {
                fileIn.get();
            }   
            lineNr++;
        }


        //Parsing first token of line
        if(token != ""){
            Specification spec;
            spec.setShape(parseShape(token));

            //Shape parser has an edge case where 2 tokens make up SEMICIRCLE. Luckily 
            //the first token is unique so I'll just double check the last one;)
            if (spec.getShape() == SpecFinder::SEMICIRCLE)
            {
                token = "";
                fileIn >> token;
                //Second check in case of SEMICIRCLE
                if(parseShape(token) != SpecFinder::CIRCLE){
                    std::cout << "Fout! Er staat alleen het woord \"halve\" in de specificatie. Programma-output klopt mogelijk niet. Regel: " << std::to_string(lineNr) << std::endl;
                }

            }
            token = "";
            fileIn >> token;
            //Parse next token to get the color
            if(token != ""){
                spec.setColor(parseColor(token));
            }
            if(spec.getColor() != SpecFinder::UNKNOWN_COLOR && spec.getShape() != SpecFinder::UNKNOWN_SHAPE)
            {
                SpecFinder s(spec);
                specFinders.push_back(s);
            }else{
                std::cout << "Fout! Verkeerde specificatie opgegeven op regel: " << std::to_string(lineNr) << std::endl;
            }


        }
        lineNr++;
    }
    
    
    return specFinders;
}

/**
 * @brief: Parses a single word token string, and returns
 * an int representing the SpecFinder::ColorSpecs enum.
*/
/*static*/ int Parser::parseColor(std::string& token){
    if (token == "roze")
    {
        return SpecFinder::PINK;
    }
    else if(token == "oranje")
    {
        return SpecFinder::ORANGE;
    }
    else if (token == "groen")
    {
        return SpecFinder::GREEN;
    }
    else if (token == "geel")
    {
        return SpecFinder::YELLOW;
    }
    else
    {
        return SpecFinder::UNKNOWN_COLOR;
    }
}

/**
 * @brief: Parses a single word token string, and returns
 * an int representing the SpecFinder::Shapespecs enum.
 * input string "halve" yields SEMICIRCLE as a result,
 * it is up to the developer to check for a "cirkel"-
 * token afterwards.
*/
/*static*/ int Parser::parseShape(std::string& token){
    if(token == "cirkel")
    {
        return SpecFinder::CIRCLE;
    }
    else if (token == "rechthoek")
    {
        return SpecFinder::RECTANGLE;
    }
    else if (token == "vierkant")
    {
        return SpecFinder::SQUARE;
    }
    else if (token == "halve")
    {
        return SpecFinder::SEMICIRCLE;
    }
    else
    {
        return SpecFinder::UNKNOWN_SHAPE;
    }
    
}