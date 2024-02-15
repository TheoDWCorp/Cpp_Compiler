#include <iostream>
#include <string>
#include "Token.hpp"
#include "Constante.hpp"

using namespace std;

#ifndef STRINGCONSTANTE_HPP
#define STRINGCONSTANTE_HPP

class StringConstante : public Constante{ //StringConstante hérite de Constante
public :
    string value; 
    
    StringConstante(int i, string v, int l,int nb_char){
        name = "string_constante"; //tous les tokens de classe StringConstante auront comme structure <"string_constante";value;index>
        index = i;
        line = l;
        value = v;
        nb_character = nb_char;
    }

    void printToken(){
        cout << "<string_constante;" << value << ";" << index << "> \n";
    };
};


#endif