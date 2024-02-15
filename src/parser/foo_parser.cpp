#include <iostream>
#include <vector>
#include "../table_analyse/table_analyse.hpp"
#include <unordered_map>

#include "foo_parser.hpp"
using namespace std;


void test_ta(){
    vector<vector<string>> table_analyse = get_table_analyse("../table_analyse/table_analyse.csv");
    int i=0;
    int j=0;
    for (vector<string> col : table_analyse) {
        j=0;
        for (string str : col) {
            if (str==""){
                //cout<<j<<" ";
            }
            else {
                cout << str << " ";
            }
            j++;            
        }
        cout<<endl;
        i++;
    }
}
void test_red(){
    vector<Reduction> liste_reductions = get_liste_reduction("../table_analyse/liste_reductions.txt", '#', '&');
    for (Reduction red:liste_reductions){
        cout<<red.non_terminal<<" : ";
        for (Element e: red.liste_elements){
            cout<<e.value<< " ";
        }
        cout<<endl;

    }
}
unordered_map<string, int> create_map_index_column(vector<vector<string>> table_analyse ) {
    unordered_map<string, int> map;
    
    int i=0;
    for (string str:table_analyse[0]){
        map[str]=i++;
    }
    return map;
}

string getAction(vector<vector<string>> table_analyse,string element, string state) {
    unordered_map<string, int> map = create_map_index_column(table_analyse);
    
    //recup du numero de ligne
    string subString = state.substr(1);
    int ligne = stoi(subString)+1; //
    //cout<<ligne<<","<<map[element]<<endl;

    return (table_analyse[ligne])[(map[element])];
}

string getAction(vector<vector<string>> table_analyse,string element, int state) {
    unordered_map<string, int> map = create_map_index_column(table_analyse);
    
    int ligne = state+1;
    //cout<<ligne<<","<<map[element]<<endl;

    return (table_analyse[ligne])[(map[element])];
}

int get_length_reduction(int index_reduction){
    //path en dur
    vector<Reduction> liste_reductions = get_liste_reduction("../table_analyse/liste_reductions.txt", '#', '&');
    return liste_reductions[index_reduction].liste_elements.size();
}

string get_res_reduction(int index_reduction){
    //path en dur
    vector<Reduction> liste_reductions = get_liste_reduction("../table_analyse/liste_reductions.txt", '#', '&');
    return liste_reductions[index_reduction].non_terminal;
}

vector<string> getExpected(vector<vector<string>> table_analyse,int state){
    vector<string> expected;
    for (int i=1;i<table_analyse[0].size();i++){
        if (table_analyse[state+1][i]!=""){
            expected.push_back(table_analyse[0][i]);
        }
    }
    return expected;
}