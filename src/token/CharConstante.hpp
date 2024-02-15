#include <iostream>
#include <string>
#include "Token.hpp"
#include "Constante.hpp"

using namespace std;

#ifndef CHARCONSTANTE_HPP
#define CHARCONSTANTE_HPP

class CharConstante : public Constante{ //CharConstante hérite de Constante
public :
    char value; 
    
    CharConstante(int i, char v, int l,int nb_char){
        name = "char_constante"; //tous les tokens de classe CharConstante auront comme structure <"char_constante";value;index>
        index = i;
        line = l;
        value = v;
        nb_character = nb_char;
    }

    void printToken(){
        cout << "<char_constante;" << value << ";" << index << "> \n";
    };
};


#endif