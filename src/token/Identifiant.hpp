#include <iostream>
#include <string>
#include "Token.hpp"

using namespace std;

#ifndef IDENTIFIANT_HPP
#define IDENTIFIANT_HPP

class Identifiant : public Token{ //Identifiant hérite de Token
public :
    string idf;
    int value;

    Identifiant(int i, int l, string s, int v,int nb_char){
        name = "Identifiant"; //tous les tokens de classe keyword auront comme structure <"identifiant";index;idf;value>
        index = v;//dans le lexique
        line = l;//dans la src
        idf = s;
        value = i;//dans la tds
        nb_character = nb_char;
    }

    void printToken(){
        cout << "<keyword;" << value << ";" << idf << ";" << index << "> "<<endl;
    };
};


#endif