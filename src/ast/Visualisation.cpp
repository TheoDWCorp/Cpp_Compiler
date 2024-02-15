#include <fstream>
#include <string>
#include <iostream>
#include <queue>
#include <unordered_map> 

#include "TreeNode.hpp"
#include "Visualisation.hpp"
#include "../token/Identifiant.hpp"
#include "../token/Keyword.hpp"
#include "../token/Operateur.hpp"
#include "../token/Constante.hpp"
#include "../token/BoolConstante.hpp"
#include "../token/CharConstante.hpp"
#include "../token/FloatConstante.hpp"
#include "../token/IntConstante.hpp"
#include "../token/Identifiant.hpp"
#include "../token/StringConstante.hpp"

using namespace std;

void parcoursEnLargeur(TreeNode* root) {
    string filename = "arbre_syntaxique.puml";
    ofstream out(filename);
    out << "@startuml arbre_syntaxique" << endl;
    out << "hide methods" << endl;
    out << "hide attribute" << endl;
    out << "hide circle" << endl;

    if (root == nullptr) return;

    queue<TreeNode*> queue;
    int i=0;
    root->id = i;
    Symbole symbole = Symbole();
    symbole.representation = "root";
    symbole.is_terminal = false;
    root->symbole = symbole;
    queue.push(root);
    while (!queue.empty()) {
        TreeNode* current = queue.front();
        queue.pop();
        current->symbole.representation=getRepr(current);

        out << "class \""<<current->id<<" : " << current->symbole.representation << "\"{}"<< endl;
        if (current->pere != nullptr) {
            out << "\""<<current->pere->id<<" : " <<current->pere->symbole.representation << "\""<< " --> " << "\""<<current->id<<" : "<< current->symbole.representation << "\""<< endl;
        }

        for (TreeNode* child : current->fils) {
            child->id = ++i;
            queue.push(child);
        }
        
    }

    out << "@endmindmap" << endl;
    out.close();
}


string getRepr(TreeNode* node) {

    if (node->symbole.is_terminal) {
        if (getKeyWord((stoi(node->symbole.representation))) != "r") {
            string name = getKeyWord((stoi(node->symbole.representation)));
            return name;
        }
        else {
            Symbole symbole = node->symbole;
            Token* token = symbole.token;
            string name = token->name;
            if (name=="Identifiant"){
                name=(dynamic_cast<Identifiant*>(token))->idf;
            }
            else if (name=="int_constante"){
                name=to_string((dynamic_cast<IntConstante*>(token))->value);
            }
            else if (name=="bool_constante"){
                name=to_string((dynamic_cast<BoolConstante*>(token))->value);
            }
            else if (name=="float_constante"){
                name=to_string((dynamic_cast<FloatConstante*>(token))->value);
            }
            else if (name=="char_constante"){
                name=((dynamic_cast<CharConstante*>(token))->value);
            }
            else if (name=="string_constante"){
                name=(dynamic_cast<StringConstante*>(token))->value; 
            }
            return name;
        }
        
    }
    else {
        return node->symbole.representation;
    }
}


string getKeyWord(int index){
    
    unordered_map<int, string> lexique; 
    lexique[0]="and";
    lexique[1]="begin";
    lexique[2]="else";
    lexique[3]="elsif";
    lexique[4]="end";
    lexique[5]="for";
    lexique[6]="function";
    lexique[7]="if";
    lexique[8]="in";
    lexique[9]="is";
    lexique[10]="loop";
    lexique[11]="not";
    lexique[12]="null";
    lexique[13]="or";
    lexique[14]="out";
    lexique[15]="procedure";
    lexique[16]="record";
    lexique[17]="rem";
    lexique[18]="return" ;
    lexique[19]="reverse";
    lexique[20]="then";
    lexique[21]="type";
    lexique[22]="use";
    lexique[23]="while";
    lexique[24]="with";

    //opérateur
    lexique[30]="+";
    lexique[31]="-";
    lexique[32]="/";
    lexique[33]="*";
    lexique[34]="<";
    lexique[35]=">";
    lexique[36]="=";
    lexique[37]="/=";
    lexique[38]="<=";
    lexique[39]=">=";
    lexique[40]=":=";

    //séparateur
    lexique[41]=":";
    lexique[42]=";";
    lexique[43]="(";
    lexique[44]=")";
    lexique[45]=".";
    lexique[46]=",";
    lexique[47]="'";
    if (lexique.count(index) == 0) {
        return "r";
    }
    else {
        return lexique[index];
    }
}