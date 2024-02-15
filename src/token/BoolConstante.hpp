#include <iostream>
#include <string>
#include "Token.hpp"
#include "Constante.hpp"

using namespace std;

#ifndef BOOLCONSTANTE_HPP
#define BOOLCONSTANTE_HPP

class BoolConstante : public Constante{ //BoolConstante hérite de Constante
public :
    bool value; 
    
    BoolConstante(int i, bool v, int l,int nb_char){
        name = "bool_constante"; //tous les tokens de classe BoolConstante auront comme structure <"bool_constante";value;index>
        index = i;
        line = l;
        value = v;
        nb_character = nb_char; 
    }

    void printToken(){
        if (value == true){
            cout << "<bool_constante;true;" << index << "> \n";
        }
        else{
            cout << "<bool_constante;false;" << index << "> \n";
        }
    };
};


#endif