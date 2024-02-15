#include <iostream>
#include <string>
#include "Token.hpp"

using namespace std;

#ifndef OPERATEUR_HPP
#define OPERATEUR_HPP

class Operateur : public Token{ //Operateur hérite de Token
public :
    Operateur(int i, int l,int nb_char){
        name = "operateur"; //tous les tokens de classe operateur auront comme structure <"operateur";index>
        index = i;
        line = l;
        nb_character = nb_char;
    }


    void printToken(){
        cout << "<operateur;" << index << "> \n";
    };
};


#endif