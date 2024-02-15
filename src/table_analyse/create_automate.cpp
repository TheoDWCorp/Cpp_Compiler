#include "automate.hpp"


int main() {
    
    vector<Etat> automate;
    vector<Transition> liste_transitions;

    string grammaire_path ="./grammaires/grammaire_sujet.txt";
    string non_terminal_augmente = "fichier'";

    //string grammaire_path = "./grammaires/grammaire3.txt";
    //string non_terminal_augmente = "E'";

    bool automate_LALR1 = true; // false -> LR(1), true -> LALR(1)
    // ce token ne peut pas être un caractère réservé en regex (exemple : '+'  '?'  '.'  '['  '\'  etc...)
    // si ce token est présent dans la grammaire il faut soit changer soit l'enlever et l'ajouter après
    char token_non_terminal = '#', token_terminal='&';

    Etat grammaire;
    unordered_set<string> ensemble_terminaux;
    vector<Reduction> liste_reductions;
    int grammaire_incorrect = get_grammaire(grammaire, grammaire_path, token_non_terminal, token_terminal, ensemble_terminaux, liste_reductions);
    save_liste_reductions("liste_reductions.txt", liste_reductions, token_non_terminal, token_terminal);


    // on vérifie si la grammaire est correct ou non
    if (grammaire_incorrect) {
        cerr << "La grammaire est incorrect ";
        if (grammaire_incorrect>0) cerr << "(ligne : " << grammaire_incorrect << ")\n";
        else cerr << "(non terminal présent dans un item mais absent de la grammaire)\n";
        return 0;
    }
    //show_etat(grammaire);
    

    // on vérifie que le non terminal augmenté est bien le bon
    if (grammaire.map_items.find(non_terminal_augmente)==grammaire.map_items.end()) {
        cerr << "Le terminal augmenté n'est pas le bon (" << non_terminal_augmente << ")\n"; return 0;
    }
    
    

    // on calcule les premiers de chaque non terminal de la grammaire pour pouvoirs calculer les premiers de n'importe quel item plus tard
    unordered_map<string, unordered_set<string>> premiers_grammaire;
    premiers_grammaire_initialisation(grammaire, premiers_grammaire);
    //show_premiers(grammaire, premiers_grammaire);
    
    
    

    // création d'I0
    vector<pair<string, Item>> liste_items_a_ajouter = {make_pair(non_terminal_augmente, grammaire.map_items[non_terminal_augmente][0])};
    liste_items_a_ajouter[0].second.contexte = {"$"};
    automate.push_back(nouvel_etat(grammaire, liste_items_a_ajouter, premiers_grammaire));
    
    cout << "etat : 0\n";
    //show_etat(automate[0]);

    

    // on calcule tous les etats
    for (int i=0; i<automate.size(); i++) {
        avancement_etat(i, automate, grammaire, premiers_grammaire, liste_transitions, automate_LALR1); // on génère tous les nouveaux états possible à partir de l'etat i
        if (i+1!=automate.size()) {
            cout << "etat : " << i+1 << "\n";
            //show_etat(automate[i+1]);
        }
    }

    //show_transitions(liste_transitions);

    // création du diagramme uml représentant l'automate et la grammaire
    string uml_path="./uml.puml";
    if (automate.size()<50) {
        create_uml(uml_path, automate, liste_transitions, grammaire, automate_LALR1); // sudo apt install graphviz
    }
    

    // création de la table d'analyse
    create_table_analyse(automate, liste_transitions, grammaire, ensemble_terminaux);

    return 0;
}