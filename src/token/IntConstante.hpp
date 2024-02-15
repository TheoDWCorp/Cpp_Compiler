#include <iostream>
#include <string>
#include "Token.hpp"
#include "Constante.hpp"

using namespace std;

#ifndef INTCONSTANTE_HPP
#define INTCONSTANTE_HPP

class IntConstante : public Constante{ //IntConstante hérite de Constante
public :
    int value; 

    IntConstante(int i, int v, int l,int nb_char){
        name = "int_constante"; //tous les tokens de classe IntConstante auront comme structure <"int_constante";value;index>
        index = i;
        line = l;
        value = v;
        nb_character = nb_char;
    }

    void printToken(){
        cout << "<int_constante;" << value << ";" << index << "> \n";
    };
};


#endif