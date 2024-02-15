#include <fstream>
#include "grammaire_classes.hpp"

using namespace std;


vector<vector<string>> get_table_analyse(string table_analyse_path) {
    vector<vector<string>> table_analyse;

    ifstream table_analyse_file(table_analyse_path);
    if (!table_analyse_file) {
        cerr << "aucun fichier à l'emplacement : " << table_analyse_path << "\n";
        return table_analyse;
    }

    
    string line;
    while (getline(table_analyse_file, line)) {
        table_analyse.push_back(vector<string>(0));
        string temp;
        bool flag=true; // to avoid : "
        for (auto letter:line) {
            if (flag) {flag=false; continue;}
            if (letter==',') {
                temp.pop_back(); // remove the last "
                table_analyse.back().push_back(temp);
                temp=""; flag=true;
            } else temp.push_back(letter);
        }
        
        if (temp!="") {
            temp.pop_back();
            table_analyse.back().push_back(temp);
        }
    }
    table_analyse_file.close();

    return table_analyse;
}


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




vector<Reduction> get_liste_reduction(string liste_reductions_path, char token_non_terminal, char token_terminal) {
    vector<Reduction> liste_reductions;

    ifstream liste_reductions_file(liste_reductions_path);
    if (!liste_reductions_file) {
        cerr << "aucun fichier à l'emplacement : " << liste_reductions_path << "\n";
        return liste_reductions;
    }

    
    string line;
    while (getline(liste_reductions_file, line)) {
        string non_terminal="";
        int i=0;
        while (i<line.size()) { // on recupère le non terminal
            if (line[i]==' ') break;
            non_terminal.push_back(line[i]);
            i++;
        }
        i+=4; // on passe " -> "

        string temp="";
        bool flag_non_terminal=false, flag_terminal=false;
        vector<Element> liste_elements;
        while(i<line.size()) {
            if (line[i]==token_non_terminal) {
                if (flag_non_terminal) {
                    liste_elements.push_back(Element(temp, false));
                    temp="";
                }
                flag_non_terminal=!flag_non_terminal;
            } else if (line[i]==token_terminal) {
                if (flag_terminal) {
                    liste_elements.push_back(Element(temp, true));
                    temp="";
                }
                flag_terminal=!flag_terminal;
            } else temp.push_back(line[i]);
            i++;
        }
        liste_reductions.push_back(Reduction(non_terminal, liste_elements));
    }
    liste_reductions_file.close();

    return liste_reductions;
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

