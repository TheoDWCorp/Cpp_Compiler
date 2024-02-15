#ifndef TOKEN_HPP
#define TOKEN_HPP

#include <iostream>
#include <string>

using namespace std;


class Token{ //s'affiche sous la forme <name;index> sauf idantifiant
public:
    string name;
    int index;
    int line; //permet de renvoyer la ligne en cas d'erreur syntaxique
    int nb_character;
    Token(){};
    virtual void printToken() = 0; //le mot clé "virtual" permet l'override de la fonction, ie d'assurer le statut abstrait de la classe Token
};


#endif