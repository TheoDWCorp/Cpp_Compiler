#include <iostream>
#include <string>
#include <vector>

#include "../tds/Identifier.hpp"

#include "../token/Token.hpp"
#include "../token/Keyword.hpp"
#include "../token/Operateur.hpp"
#include "../token/Constante.hpp"
#include "../token/BoolConstante.hpp"
#include "../token/CharConstante.hpp"
#include "../token/FloatConstante.hpp"
#include "../token/IntConstante.hpp"
#include "../token/Identifiant.hpp"


#include "lexeur.hpp"
#include "../tds/TableDesSymboles.hpp"


int main(int argc, char* argv[]){
    if (argc<4) return 1;
    //path outputLexeme outputToken
    string sourceFile = argv[1];
    bool outputLexeme = argv[2][0]=='1';
    bool outputToken = argv[3][0]=='1';
    bool outputTds = argv[4][0]=='1';

    string path=""; // par exemple : ./result.txt
    if (argc>=6) path=argv[5];


    TableDesSymboles* table = new TableDesSymboles();

    vector<Token*> tokens= lexeur(sourceFile,outputLexeme,outputToken,table,path, false);
    
    if (outputTds){
        cout << "TABLE DES SYMBOLES"<<endl;
        table->printTable();
    }

}