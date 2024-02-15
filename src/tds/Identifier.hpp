#include <iostream>
#include <string>

using namespace std;

#ifndef IDENTIFIER_H
#define IDENTIFIER_H

class Identifier {
public :
    string idf;
    int line;

    Identifier(string s, int l){
        idf = s;
        line = l;
    }
    void printIdf(){
    cout << "(" << idf << ";" << line << ") \n";//affiche l'élément avec la syntaxe suivante (nom,numéro_ligne)
    }

};

#endif