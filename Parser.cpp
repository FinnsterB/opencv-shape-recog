#include "Parser.h"

#include <fstream>
#include <iostream>

bool Parser::checkComment(std::string &token)
{
    std::string filtered;
    bool containsComment = false;
    for (char c : token) {
        if (c == '#') {
            containsComment = true;
            break; // Stop at '#'
        }
        filtered += c; // Append valid characters
    }
    token = filtered;
    return containsComment;
}

Parser::Parser(/* args */)
{
}

Parser::~Parser()
{
}

/*static*/ std::vector<SpecFinder> Parser::parse(const std::string &file)
{   
    std::ifstream fileIn;
    std::string token;
    std::string unfilteredToken;
    std::string wrongColorToken;
    std::string wrongShapeToken;
    std::vector<SpecFinder> specFinders;
    int lineNr = 1;

    fileIn.open(file);
    while (!fileIn.eof())
    {
        

        fileIn >> token;
        //Check if entire line is a comment and clear if it is
        if(checkComment(token))
        {
            while(fileIn.peek() != '\n')
                {
                    fileIn.get();
                }
        }


        //Parsing first token of line
        if(token != ""){
            if (checkComment(token))
            {
                std::cout << "Fout! Regel " << lineNr << " slechts deels ingevuld. Overgeslagen!" << std::endl;
                while(fileIn.peek() != '\n')
                {
                    fileIn.get();
                }
                continue;
            }
            Specification spec;
            spec.setShape(parseShape(token));
            if(spec.getShape() == UNKNOWN_SHAPE)
            {
                wrongShapeToken = token;
            }
            //Shape parser has an edge case where 2 tokens make up SEMICIRCLE. Luckily 
            //the first token is unique so I'll just double check the last one;)
            if (spec.getShape() == SEMICIRCLE)
            {
                token = "";
                fileIn >> token;
                //Second check in case of SEMICIRCLE
                if(parseShape(token) != CIRCLE)
                {
                    std::cout << "Fout! Er staat alleen het woord \"halve\" in de specificatie. Programma-output klopt mogelijk niet. Regel: " << std::to_string(lineNr) << std::endl;
                }

            }
            token = "";
            fileIn >> token;
            //Parse next token to get the color
            if(token != "")
            {
                checkComment(token);
                spec.setColor(parseColor(token));
                if(spec.getColor() == UNKNOWN_COLOR)
                {
                    wrongColorToken = token;
                }
                //Clear the rest of the line
                while(fileIn.peek() != '\n')
                {
                    fileIn.get();
                    if(fileIn.eof()){
                        break;
                    }
                }
            }
            if(spec.getColor() != UNKNOWN_COLOR && spec.getShape() != UNKNOWN_SHAPE)
            {
                SpecFinder s(spec);
                specFinders.push_back(s);
            }
            else
            {
                if(spec.getColor() == UNKNOWN_COLOR)
                {
                    std::cout << "Fout! Verkeerde kleur \"" << wrongColorToken << "\" opgegeven op regel: " << std::to_string(lineNr) << " Kies uit: oranje, geel, groen of roze." << std::endl;
                    wrongColorToken = "";
                }
                if(spec.getShape() == UNKNOWN_SHAPE)
                {
                    std::cout << "Fout! Verkeerde vorm \"" << wrongShapeToken << "\" opgegeven op regel: " << std::to_string(lineNr) << " Kies uit: vierkant, rechthoek, cirkel, driehoek of halve cirkel." << std::endl;
                    wrongShapeToken = "";
                }
            }
        }
        lineNr++;
    }
    
    
    return specFinders;
}

void Parser::parseLine(const std::string &line, std::vector<SpecFinder>& specFinders)
{
    std::stringstream ssLine(line);
    std::string token = "";

    ssLine >> token;

    //Exit when user types exit
    if(token == "exit"){
        exit(0);
    }

    //Parsing first token of line
    if(token != ""){
        Specification spec;
        spec.setShape(parseShape(token));

        //Shape parser has an edge case where 2 tokens make up SEMICIRCLE. Luckily 
        //the first token is unique so I'll just double check the last one;)
        if (spec.getShape() == SEMICIRCLE)
        {
            token = "";
            ssLine >> token;
            //Second check in case of SEMICIRCLE
            if(parseShape(token) != CIRCLE){
                std::cout << "Fout! Er staat alleen het woord \"halve\" in de specificatie." << std::endl;
            }

        }
        token = "";
        ssLine >> token;
        //Parse next token to get the color
        if(token != ""){
            spec.setColor(parseColor(token));
        }
        if(spec.getColor() != UNKNOWN_COLOR && spec.getShape() != UNKNOWN_SHAPE)
        {
            for(SpecFinder otherSpec : specFinders){
                if (spec.getColor() == otherSpec.spec.getColor() && spec.getShape() == otherSpec.spec.getShape())
                {
                    return;
                }
                
            }
            
            SpecFinder s(spec);
            specFinders.push_back(s);
        }else{
            if(spec.getColor() == UNKNOWN_COLOR){
                std::cout << "Fout! Verkeerde specificatie opgegeven!" << " Onbekende kleur! Kies uit: oranje, geel, groen of roze." << std::endl;
            }
            if(spec.getShape() == UNKNOWN_SHAPE){
                std::cout << "Fout! Verkeerde specificatie opgegeven!" << " Onbekende vorm! Kies uit: vierkant, rechthoek, cirkel, driehoek of halve cirkel." << std::endl;
            }
        }


    }
}

/**
 * @brief: Parses a single word token string, and returns
 * an int representing the ColorSpecs enum.
*/
/*static*/ int Parser::parseColor(const std::string& token){
    if (token == "roze")
    {
        return PINK;
    }
    else if(token == "oranje")
    {
        return ORANGE;
    }
    else if (token == "groen")
    {
        return GREEN;
    }
    else if (token == "geel")
    {
        return YELLOW;
    }
    else
    {
        return UNKNOWN_COLOR;
    }
}

/**
 * @brief: Parses a single word token string, and returns
 * an int representing the Shapespecs enum.
 * input string "halve" yields SEMICIRCLE as a result,
 * it is up to the developer to check for a "cirkel"-
 * token afterwards.
*/
/*static*/ int Parser::parseShape(const std::string& token){
    if(token == "cirkel")
    {
        return CIRCLE;
    }
    else if (token == "driehoek")
    {
        return TRIANGLE;
    }
    else if (token == "rechthoek")
    {
        return RECTANGLE;
    }
    else if (token == "vierkant")
    {
        return SQUARE;
    }
    else if (token == "halve")
    {
        return SEMICIRCLE;
    }
    else
    {
        return UNKNOWN_SHAPE;
    }
    
}