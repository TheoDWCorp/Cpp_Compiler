#include <iostream>
#include <string>
#include "Token.hpp"

using namespace std;

#ifndef KEYWORD_HPP
#define KEYWORD_HPP

class Keyword : public Token{ //Keyword hérite de Token
public :
    Keyword(int i, int l,int nb_char){
        name = "keyword"; //tous les tokens de classe keyword auront comme structure <"keyword";index>
        index = i;
        line = l;
        nb_character = nb_char;
    }

    void printToken(){
        cout << "<keyword;" << index << "> \n";
    };
};


#endif