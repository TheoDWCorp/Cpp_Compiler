#include <iostream>
#include <string>
#include "Token.hpp"

using namespace std;

#ifndef CONSTANTE_HPP
#define CONSTANTE_HPP

class Constante : public Token{ //Constante hérite de Token
public :
    Constante(){};

    void printToken() = 0;
};


#endif