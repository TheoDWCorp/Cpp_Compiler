#include <fstream>
#include <unistd.h>
#include <cstring>
#include <regex>
#include "grammaire_classes.hpp"



int get_grammaire(Etat& grammaire, string grammaire_path, char token_non_terminal, char token_terminal, unordered_set<string>& ensemble_terminaux, vector<Reduction>& liste_reductions) {
    ifstream grammaire_file(grammaire_path);

    regex grammaire_regex_first_line("^(\\s)*(\\S)+(\\s)+->.*\\S.*$"); 
    // espace(s) optionnel(s)    charactère(s)     espace(s)    ->    charactère(s)


    regex grammaire_regex_other_lines("^(\\s)*(\\S)*(\\s)+->.*\\S.*$"); 
    // espace(s) optionnel(s)    charactère(s) optionnel(s)     espace(s)    ->   charactère(s) 

    string line, non_terminal="";
    int nb_line=1; // 1-index
    while(getline(grammaire_file, line)) {
        // on vérifie que la ligne est correct du point de vue d'une grammaire
        if (non_terminal=="") {
            if (!regex_search(line, grammaire_regex_first_line)) return nb_line; // la première ligne de la grammaire n'est pas correct
        } else if (!regex_search(line, grammaire_regex_other_lines)) return nb_line; // la grammaire n'est pas correct
        if (line[0]!=' ') non_terminal="";

        int i=0;
        while (i<line.size()) { // recupère le non terminal, si il y en a pas (deux items pour un même non terminal) on utilise celui d'avant 
            if (line[i]==' ') break;
            non_terminal.push_back(line[i]);
            i++;
        }

        // on suppose que la grammaire est bien écrite (pas de -> avec rien après par exemple et il y a obligatoirement une flèche ->)
        while (line[i]!='>') i++; // on passe la flèche
        i++;
        while (line[i]==' ') i++; // on passe les espaces
        
        if (line[i]!=token_non_terminal&&line[i]!=token_terminal) return nb_line;

        string temp="";
        bool flag_non_terminal=false, flag_terminal=false;
        vector<Element> liste_elements;
        while(i<line.size()) {
            if (line[i]==token_non_terminal) {
                if (flag_terminal) return nb_line; // le terminal d'avant n'était pas terminé
                if (flag_non_terminal) {
                    liste_elements.push_back(Element(temp, false));
                    temp="";
                }
                flag_non_terminal=!flag_non_terminal;
            } else if (line[i]==token_terminal) {
                if (flag_non_terminal) return nb_line; // le non terminal d'avant n'était pas terminé
                if (flag_terminal) {
                    liste_elements.push_back(Element(temp, true));
                    ensemble_terminaux.insert(temp);
                    temp="";
                }
                flag_terminal=!flag_terminal;
            } else temp.push_back(line[i]);
            i++;
        }

        if (flag_non_terminal) return nb_line; // un non terminal n'a pas été terminé

        grammaire.map_items[non_terminal].push_back(Item(liste_elements, 0, {}, nb_line-1));
        liste_reductions.push_back(Reduction(non_terminal, liste_elements));
        nb_line++;
        
    }
    grammaire_file.close();


    // on vérifie que tous les non terminaux dans les items sont présents dans la grammaire
    for (auto pair:grammaire.map_items) {
        for (auto item:pair.second) {
            for (auto element:item.liste_elements) {
                if (!element.is_terminal&&grammaire.map_items.find(element.value)==grammaire.map_items.end()) {
                    cout << "Non terminal problématique : " << element.value << "\n";
                    return -1; // non terminal présent dans un item mais absent de la grammaire
                }
            }
        }
    }


    return 0;
}





unordered_set<string> aux_premiers_grammaire_initialisation(Item& item, Etat& grammaire, unordered_map<string, unordered_set<string>>& premiers_grammaire, unordered_map<string, int>& non_terminal_selected) {
    if (item.liste_elements[0].is_terminal) return {item.liste_elements[0].value}; // terminal

    if (non_terminal_selected[item.liste_elements[0].value]==1) return {}; // en cours
    if (non_terminal_selected[item.liste_elements[0].value]==2) return premiers_grammaire[item.liste_elements[0].value]; // fini


    non_terminal_selected[item.liste_elements[0].value]=1; // de "pas selectionné" à "en cours"
    for (auto new_item:grammaire.map_items[item.liste_elements[0].value]) { // non terminal
        unordered_set<string> premiers = aux_premiers_grammaire_initialisation(new_item, grammaire, premiers_grammaire, non_terminal_selected);
        for (auto terminal:premiers) premiers_grammaire[item.liste_elements[0].value].insert(terminal);
    }
    non_terminal_selected[item.liste_elements[0].value]=2; // de "en cours" à "fini"


    return premiers_grammaire[item.liste_elements[0].value];
}



void premiers_grammaire_initialisation(Etat& grammaire, unordered_map<string, unordered_set<string>>& premiers_grammaire) {
    unordered_map<string, int> non_terminal_selected; // 0 -> pas selectionné, 1 -> en cours, 2 -> fini
    for (auto x:grammaire.map_items) {
        Item item({Element(x.first, false)}, 0, {}, 0);
        aux_premiers_grammaire_initialisation(item, grammaire, premiers_grammaire, non_terminal_selected);
    }
}


// premiers d'un item (à partir de son index)
unordered_set<string> premiers(Item& item, unordered_map<string, unordered_set<string>>& premiers_grammaire) {
    if (item.liste_elements[item.index].is_terminal) return {item.liste_elements[item.index].value}; // terminal
    return premiers_grammaire[item.liste_elements[item.index].value]; // non terminal
}




Etat nouvel_etat(Etat& grammaire, vector<pair<string, Item>> liste_items_a_ajouter, unordered_map<string, unordered_set<string>>& premiers_grammaire) {
    Etat new_etat;
    for (int i=0; i<liste_items_a_ajouter.size(); i++) {
        pair<string, Item> pair=liste_items_a_ajouter[i]; // pair non terminal, item
        
        // il faut verifier si cet item existe déjà ou non dans new_etat
        bool flag_nouvel_item=true, flag_meme_contexte=true; // pas vraiment même contexte mais plutôt si le contexte a des elements nouveaux
        for (int i=0; i<new_etat.map_items[pair.first].size(); i++) {
            Item& item=new_etat.map_items[pair.first][i];
            if (comparaison_liste_elements(item.liste_elements, pair.second.liste_elements)&&item.index==pair.second.index) {
                flag_nouvel_item=false;
                for (auto element:pair.second.contexte) {
                    if (item.contexte.find(element)==item.contexte.end()) {
                        flag_meme_contexte=false;
                        item.contexte.insert(element);
                    }
                }
                break;
            }
        }

        if (!flag_nouvel_item&&flag_meme_contexte) continue;
        else if (flag_nouvel_item) new_etat.map_items[pair.first].push_back(pair.second);
        

        if (pair.second.index!=pair.second.liste_elements.size()&&!pair.second.liste_elements[pair.second.index].is_terminal) { // l'element courant est un non terminal
            string element_courant = pair.second.liste_elements[pair.second.index].value;
            for (auto item:grammaire.map_items[element_courant]) {
                if (pair.second.liste_elements.size()==pair.second.index+1) item.contexte=pair.second.contexte;
                else {
                    pair.second.index++; // on veut les premiers de l'élément après le non terminal qui nous a amené ici
                    item.contexte=premiers(pair.second, premiers_grammaire);
                    pair.second.index--;
                }
                
                liste_items_a_ajouter.push_back(make_pair(element_courant, item));
            }
            
        }
    }

    return new_etat;
}




int aux_avancement_etat(Etat& new_etat, vector<Etat>& automate, bool automate_LALR1) {
    // il faut vérifier si cet état existe dejà ou non dans l'automate (au contexte près) et fusionner si besoin
    bool flag_etat_identique=false; // au contexte près
    int new_etat_index=automate.size(); // futur index
    for (int etat_index=0; etat_index<automate.size(); etat_index++) {
        Etat& etat = automate[etat_index];
        if (etat.map_items.size()!=new_etat.map_items.size()) continue; // pas le même nombre de clés
        bool flag_same_keys=true;
        for (auto pair:new_etat.map_items) {
            if (etat.map_items.find(pair.first)==etat.map_items.end()) {
                flag_same_keys=false; break;
            }
        }
        if (!flag_same_keys) continue; // pas les mêmes clés

        // on compare les items des deux états
        bool flag_same_items=true;
        // ces tables de correspondances vont servir à update les contextes si besoin (retrouver quels items sont égaux (au contexte près))
        unordered_map<string, unordered_map<string,int>> correspondance_new_etat;
        unordered_map<string, unordered_map<string,int>> correspondance_etat;
        for (auto pair:new_etat.map_items) {
            if (pair.second.size()!=etat.map_items[pair.first].size()) { // les listes d'items ne font pas la même taille
                flag_same_items=false; break;
            }

            unordered_map<string, int> occurence_items; // si les items sont les mêmes alors toutes les valeurs seront égales à 2


            for (int i=0; i<pair.second.size(); i++) {
                Item& item = pair.second[i];
                string temp;
                for (auto element:item.liste_elements) {
                    temp+=element.value; temp.push_back(element.is_terminal? '1':'0');
                }
                temp+=item.index;
                occurence_items[temp]++;
                correspondance_new_etat[pair.first][temp]=i;
            }

            unordered_map<string, int> mp_etat;
            for (int i=0;  i<etat.map_items[pair.first].size(); i++) { // même non terminal
                Item& item = etat.map_items[pair.first][i];
                string temp;
                for (auto element:item.liste_elements) {
                    temp+=element.value; temp.push_back(element.is_terminal? '1':'0');
                }
                temp+=item.index;
                occurence_items[temp]++;
                correspondance_etat[pair.first][temp]=i;
            }
            
            
            for (auto pair:occurence_items) {
                if (pair.second!=2) { // les items de sont pas les mêmes
                    flag_same_items=false;
                    break;
                }
            }

            if (!flag_same_items) break;
            

        }

        if (!flag_same_items) continue; // pas les mêmes items


        // à partir d'ici on considère que les etats sont les mêmes
        // Si on cherche à faire un automate LALR(1) : il faut update les contextes de l'etat qui est déjà dans l'automate
        // Si on cherche à faire un automate LR(1) : on cherche à savoir si les contextes sont les mêmes
        bool flag_same_contexte=true; // pour LR(1)
        for (auto pair:new_etat.map_items) {
            for (auto pair2:correspondance_etat[pair.first]) {
                Item& item_etat = etat.map_items[pair.first][pair2.second];
                Item& item_new_etat = new_etat.map_items[pair.first][correspondance_new_etat[pair.first][pair2.first]];

                if (automate_LALR1) {
                     // on ajoute le contexte de item_etat à item_new_etat
                    for (auto element:item_new_etat.contexte) item_etat.contexte.insert(element);
                } else {
                    if (item_etat.contexte!=item_new_etat.contexte) { // LR(1), les contextes ne sont pas les mêmes, on ne fusionne pas 
                        flag_same_contexte=false; break;
                    }
                }
            }
            if (!automate_LALR1&&!flag_same_contexte) break; // LR(1)
        }

        if (!automate_LALR1&&!flag_same_contexte) continue; // LR(1)

        flag_etat_identique=true;
        new_etat_index=etat_index;
        break; // on a trouvé un état identique et c'est le seul donc on arrête
    }   

    if (!flag_etat_identique) automate.push_back(new_etat);
    return new_etat_index;
}




void avancement_etat(int i, vector<Etat>& automate, Etat& grammaire, unordered_map<string, unordered_set<string>>& premiers_grammaire, vector<Transition>& liste_transitions, bool automate_LALR1) {
    unordered_map<string, vector<pair<string, Item>>> map_liste_items_a_ajouter;
    Etat& etat = automate[i];
    for (auto pair:etat.map_items) {
        for (auto item:pair.second) {
            if (item.index!=item.liste_elements.size()) {
                map_liste_items_a_ajouter[item.liste_elements[item.index].value].push_back(make_pair(pair.first, item));
                map_liste_items_a_ajouter[item.liste_elements[item.index].value].back().second.index++;
            }
        }
    }

    for (auto pair:map_liste_items_a_ajouter) {
        Etat new_etat = nouvel_etat(grammaire, pair.second, premiers_grammaire);
        int new_etat_index = aux_avancement_etat(new_etat, automate, automate_LALR1); // on fusionne cet etat avec un autre déjà present dans l'automate si on peut, sinon on l'ajoute à l'automate
        liste_transitions.push_back(Transition(i, new_etat_index, pair.first));
    }
}



void show_premiers(Etat& grammaire, unordered_map<string, unordered_set<string>>& premiers_grammaire) {
    for (auto x:grammaire.map_items) {
        cout << "Premiers de "<< x.first << ":\n";
        for (auto s:premiers_grammaire[x.first]) cout << s << " ";
        cout << "\n\n";
    }
}




void create_uml(string uml_path, vector<Etat>& automate, vector<Transition>& liste_transitions, Etat& grammaire, bool automate_LALR1) {
    ofstream uml_file(uml_path);
    uml_file << "@startuml Automate\n";


    uml_file << "skinparam roundcorner 20\n"
             << "skinparam backgroundColor Gainsboro\n";


    uml_file << "\nleft header\n\n <b><font size=20 color=black >  Automate déterministe ";
    if (automate_LALR1) uml_file << "LALR(1)";
    else uml_file << "LR(1)";
    uml_file << "</font>\n\nendheader\n\n";
    
    uml_file << "Card Grammaire" << " #white [\n" << "--<b>Grammaire" << "--\n";
    for (auto x:grammaire.map_items) {
        uml_file << "<b>" <<x.first << " -> ";
        string spaces(x.first.size()*2, ' ');
        for (int j=0; j<x.second.size(); j++) {
            if (j!=0) uml_file << "<b>" << spaces << " -> ";
            Item& item = x.second[j];
            for (int k=0; k<item.liste_elements.size(); k++) {
                uml_file << item.liste_elements[k].value;
            }
            uml_file << "\n";
        }
    }
    uml_file << "]\n\n";

    for (int i=0; i<automate.size(); i++) {
        uml_file << "Card I" << i << " #white [\n" << "--<b>I" << i << "--\n";
        for (auto x:automate[i].map_items) {
            uml_file << "<b>" <<x.first << " -> ";
            string spaces(x.first.size()*2, ' ');
            for (int j=0; j<x.second.size(); j++) {
                if (j!=0) uml_file << "<b>" << spaces << " -> ";
                Item& item = x.second[j];
                for (int k=0; k<item.liste_elements.size(); k++) {
                    if (k==item.index) uml_file << "•";
                    uml_file << item.liste_elements[k].value;
                }
                if (item.index==item.liste_elements.size()) uml_file << "•";
                uml_file << "  [ ";
                for (auto element:item.contexte) {
                    uml_file << element << " ";
                }
                uml_file << "]\n";
            }
        }
        uml_file << "]\n\n";
    }

    for (auto transition:liste_transitions) {
        uml_file << "I" << transition.source << " --> " << "I" << transition.destination << ": <b>" << transition.cost << "\n";
    }
    uml_file << "Grammaire -right[hidden]- I0: \"                    \"\n";
    uml_file << "@enduml";
    uml_file.close();
}




void save_liste_reductions(string filename, vector<Reduction>& liste_reduction, char token_non_terminal, char token_terminal) {
    ofstream file(filename);
    for (auto reduction:liste_reduction) {
        file << reduction.non_terminal << " -> ";
        for (auto element:reduction.liste_elements) {
            if (element.is_terminal) file << string(1, token_terminal);
            else file << string(1, token_non_terminal);
            file << element.value;
            if (element.is_terminal) file << string(1, token_terminal);
            else file << string(1, token_non_terminal);
        }
        file << "\n";
    }
    file.close();
}


// table d'analyse
void save_table_analyse(string filename, vector<vector<string>>& table_analyse) {
    ofstream csv_file(filename);
    for (int row=0; row<table_analyse.size(); row++) {
        for (int column=0; column<table_analyse[0].size()-1; column++) {
            csv_file << "\"" << table_analyse[row][column] << "\"" << ",";
        }
        csv_file << "\"" << table_analyse[row].back() << "\"" << "\n";
    }
    csv_file.close();
}


void create_table_analyse(vector<Etat>& automate, vector<Transition>& liste_transitions, Etat& grammaire, unordered_set<string>& ensemble_terminaux) {
    int nb_non_terminaux=grammaire.map_items.size(),
        nb_terminaux=ensemble_terminaux.size(),
        nb_etats=automate.size();

    vector<vector<string>> table_analyse(nb_etats+1, vector<string>(nb_non_terminaux+nb_terminaux+2, ""));
    vector<vector<string>> table_analyse_conflits(nb_etats+1, vector<string>(nb_non_terminaux+nb_terminaux+2, ""));
    
    unordered_map<string, int> map_index; // correspondance entre le terminal/non terminal et son indice dans la table d'analyse

    table_analyse[0][0]="etats";
    table_analyse_conflits[0][0]="etats";

    int index=1; // 0 c'est pour le nom des états
    for (auto terminal:ensemble_terminaux) {
        map_index[terminal]=index;
        table_analyse[0][index]=terminal;
        index++;
    }

    map_index["$"]=index;
    table_analyse[0][index]="$";
    index++;

    for (auto pair:grammaire.map_items) {
        map_index[pair.first]=index; 
        table_analyse[0][index]=pair.first;
        index++;
    }

    table_analyse_conflits=table_analyse;

    // on ajoute les réductions
    for (int i=0; i<automate.size(); i++) {
        Etat& etat = automate[i];
        table_analyse[i+1][0]="I"+to_string(i);
        table_analyse_conflits[i+1][0]="I"+to_string(i);
        for (auto pair:etat.map_items) {
            for (auto item:pair.second) {
                if (item.liste_elements.size()==item.index) { // reduction
                    for (auto non_terminal:item.contexte) {
                        if (table_analyse[i+1][map_index[non_terminal]]!="") { // conflit
                            table_analyse[i+1][map_index[non_terminal]]+=" / r"+to_string(item.id_reduction);
                            table_analyse_conflits[i+1][map_index[non_terminal]]=table_analyse[i+1][map_index[non_terminal]];
                        } else table_analyse[i+1][map_index[non_terminal]]+= "r"+to_string(item.id_reduction);
                    }
                }
            }
        }
    }

    // on ajoute les transitions
    for (auto transition:liste_transitions) {
        if (table_analyse[transition.source+1][map_index[transition.cost]]!="") { // conflit
            table_analyse[transition.source+1][map_index[transition.cost]]+=" / d"+to_string(transition.destination);
            table_analyse_conflits[transition.source+1][map_index[transition.cost]]=table_analyse[transition.source+1][map_index[transition.cost]];
        } else table_analyse[transition.source+1][map_index[transition.cost]]+="d"+to_string(transition.destination); 
    }
    
    save_table_analyse("table_analyse.csv", table_analyse);
    save_table_analyse("table_analyse_conflits.csv", table_analyse_conflits);

}



