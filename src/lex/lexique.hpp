#ifndef LEXIQUE 
#define LEXIQUE

int lexique(std::string lexeme,bool *isIn);
bool isSeparator(char e);
bool isBool(std::string lexeme,bool* isIn);
Token* determinationToken(std::string lexeme,int ligne,int nb_character,TableDesSymboles* table);
#endif