#include <iostream>
#include <string>
#include "Token.hpp"
#include "Constante.hpp"

using namespace std;

#ifndef FLOATCONSTANTE_HPP
#define FLOATCONSTANTE_HPP

class FloatConstante : public Constante{ //FloatConstante hérite de Constante
public :
    float value; 
    
    FloatConstante(int i, float v, int l,int nb_char){
        name = "float_constante"; //tous les tokens de classe FloatConstante auront comme structure <"float_constante";value;index>
        index = i;
        line = l;
        value = v;
        nb_character = nb_char;
    }

    void printToken(){
        cout << "<float_constante;" << value << ";" << index << "> \n";
    };
};


#endif