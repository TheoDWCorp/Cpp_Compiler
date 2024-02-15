#include <regex>
#include <string>
#include <fstream>
#include "grammaire_classes.hpp"
#include "../token/Token.hpp"
#include "../lex/lexeur.hpp"
#include "../tds/TableDesSymboles.hpp"


int main() {
    string grammaire_raw_path="./grammaires/grammaire_sujet_raw.txt";
    string grammaire_path="./grammaires/grammaire_sujet.txt";

    // important : le token non terminal est utilisé ici pour reconnaitres les non terminaux une fois passés dans le lexeur (pour garder le bon ordre des terminaux/non terminaux)
    // si la grammaire possède ce token il faut soit changer le moyen de detection, soit changer le token.
    // il est important que le lexeur renvoie bien quelque chose de particulier pour le token non terminal (on peut si besoin implémenter un autre token pour cette tâche)
    char token_non_terminal='#', token_terminal='&';
    bool affichage_debug=true;
    



    ifstream grammaire_raw_file(grammaire_raw_path);

    ofstream grammaire_file(grammaire_path); // output
    if (!grammaire_file) {
        cerr << "le fichier pour la gramaire de sortie n'existe pas";
        return 0;
    }

    regex grammaire_regex_first_line("^(\\s)*(\\S)+(\\s)+->.*\\S.*$"); 
    // espace(s) optionnel(s)    charactère(s)     espace(s)    ->    charactère(s)

    regex grammaire_regex_other_lines("^(\\s)*(\\S)*(\\s)+->.*\\S.*$"); 
    // espace(s) optionnel(s)    charactère(s) optionnel(s)     espace(s)    ->   charactère(s) 

    string line;
    int nb_line=1; // 1-index
    while(getline(grammaire_raw_file, line)) {
        int i=0;
        while (line[i]!='>') i++; // on passe la flèche
        i++;
        while (line[i]==' ') i++; // on passe les espaces

        grammaire_file << line.substr(0,i);
        if (affichage_debug) cout << "Ligne : " << line.substr(i, line.size()-i) << "\n";

        string temp="", new_line="";
        bool flag_non_terminal=false;
        vector<string> liste_non_terminaux;
        string token_non_terminal_with_spaces(3, ' '); token_non_terminal_with_spaces[1]=token_non_terminal;
        while(i<line.size()) {
            if (line[i]==token_non_terminal) {
                if (flag_non_terminal) { // fin du non terminal
                    liste_non_terminaux.push_back(temp);
                    new_line+=token_non_terminal_with_spaces;
                } else new_line+=temp;
                temp="";
                flag_non_terminal=!flag_non_terminal;
            } else temp.push_back(line[i]);
            i++;
        }
        new_line+=temp;
        
        if (flag_non_terminal) return nb_line; // un non terminal n'a pas été terminé

        
        // on traite new_line avec le lexeur
        if (affichage_debug) cout << "Ligne : " << new_line << "\n";
        TableDesSymboles* tds = new TableDesSymboles();
        vector<Token*> tokens = lexeur(new_line, false, false, tds, "", true);

        // on traite les elements renvoyé par le lexeur
        int index_liste_non_terminaux=0;
        for (auto token:tokens) {
            if (affichage_debug) cout << token->index << "\n";
            if (token->index==101) {
                if (index_liste_non_terminaux==liste_non_terminaux.size()) {
                    cout << "erreur de lexeur (token 101 ligne " << nb_line << ")\n";
                    return 0;
                }
                grammaire_file << token_non_terminal << liste_non_terminaux[index_liste_non_terminaux] << token_non_terminal;
                index_liste_non_terminaux++;
                
            } else grammaire_file << token_terminal << to_string(token->index) << token_terminal;
        }
        grammaire_file << "\n";
        nb_line++;
    }
    grammaire_raw_file.close(); grammaire_file.close();

    return 0;
}