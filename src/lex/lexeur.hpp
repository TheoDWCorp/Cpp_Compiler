#include "../tds/TableDesSymboles.hpp"
#include "../token/Token.hpp"

#ifndef LEXEUR 
#define LEXEUR

std::vector<Token*> lexeur(std::string srcFile,bool outputLexeme, bool outputToken,TableDesSymboles* table, std::string path, bool bool_path);

#endif