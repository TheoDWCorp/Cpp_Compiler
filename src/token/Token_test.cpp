#include <iostream>
#include <string>
#include <vector>
#include "Token.hpp"
#include "Keyword.hpp"
#include "BoolConstante.hpp"
#include "CharConstante.hpp"
#include "FloatConstante.hpp"
#include "IntConstante.hpp"
#include "StringConstante.hpp"
#include "Operateur.hpp"
#include "Identifiant.hpp"

using namespace std;


int main(){
    //TEST 1 : Créer un token de classe Keyword et l'afficher
    Keyword k(2,1);
    k.printToken();

    //TEST 2 : idem avec un token de classe BoolConstante
    BoolConstante bc(3,true,1);
    bc.printToken();

    //TEST 3 : idem avec un token de classe CharConstante
    CharConstante cc(4,'c',1);
    cc.printToken();

    //TEST 4 : idem avec un token de classe FloatConstante
    FloatConstante fc(6,3.14,1);
    fc.printToken();

    //TEST 5 : idem avec un token de classe IntConstante
    IntConstante ic(5,2,1);
    ic.printToken();

    //TEST 6 : idem avec un token de classe StringConstante
    StringConstante sc(7,"abc",1);
    sc.printToken();

    //TEST 7 : idem avec un token de classe Operateur
    Operateur o(1,1);
    o.printToken();

    //TEST 8 : idem avec un token de classe Identifiant
    Identifiant i(9,1,"x",2);
    i.printToken();

    return 0;
}