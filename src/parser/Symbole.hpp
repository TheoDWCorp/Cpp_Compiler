#ifndef SYMBOLE_HPP
#define SYMBOLE_HPP

#include "../token/Token.hpp"
class Symbole{//permet de faire une stack d'un terminal ou d'un non terminal
public:
    bool is_terminal;
    Token* token;//token si is_terminal==true, sinon rien
    string representation;//index du token si terminal sinon nom du non terminal
    Symbole(){};
};

#endif // SYMBOLE_HPP