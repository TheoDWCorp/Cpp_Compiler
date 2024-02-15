#ifndef TABLE_ANALYSE 
#define TABLE_ANALYSE

#include "grammaire_classes.hpp" 

vector<vector<string>> get_table_analyse(string table_analyse_path);


void save_table_analyse(string filename, vector<vector<string>>& table_analyse);


vector<Reduction> get_liste_reduction(string liste_reductions_path, char token_non_terminal, char token_terminal);


void save_liste_reductions(string filename, vector<Reduction>& liste_reduction, char token_non_terminal, char token_terminal);

#endif