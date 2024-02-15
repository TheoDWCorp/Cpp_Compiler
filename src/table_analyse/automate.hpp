#ifndef AUTOMATE
#define AUTOMATE


#include "grammaire_classes.hpp"



int get_grammaire(Etat& grammaire, string grammaire_path, char token_non_terminal, char token_terminal, unordered_set<string>& ensemble_terminaux, vector<Reduction>& liste_reductions);



unordered_set<string> aux_premiers_grammaire_initialisation(Item& item, Etat& grammaire, unordered_map<string, unordered_set<string>>& premiers_grammaire, unordered_map<string, int>& non_terminal_selected);



void premiers_grammaire_initialisation(Etat& grammaire, unordered_map<string, unordered_set<string>>& premiers_grammaire);


// premiers d'un item (à partir de son index)
unordered_set<string> premiers(Item& item, unordered_map<string, unordered_set<string>>& premiers_grammaire);



Etat nouvel_etat(Etat& grammaire, vector<pair<string, Item>> liste_items_a_ajouter, unordered_map<string, unordered_set<string>>& premiers_grammaire);


int aux_avancement_etat(Etat& new_etat, vector<Etat>& automate, bool automate_LALR1);



void avancement_etat(int i, vector<Etat>& automate, Etat& grammaire, unordered_map<string, unordered_set<string>>& premiers_grammaire, vector<Transition>& liste_transitions, bool automate_LALR1);



void create_uml(string uml_path, vector<Etat>& automate, vector<Transition>& liste_transitions, Etat& grammaire, bool automate_LALR1);




void save_liste_reductions(string filename, vector<Reduction>& liste_reduction, char token_non_terminal, char token_terminal);


void save_table_analyse(string filename, vector<vector<string>>& table_analyse);


void create_table_analyse(vector<Etat>& automate, vector<Transition>& liste_transitions, Etat& grammaire, unordered_set<string>& ensemble_terminaux);

#endif