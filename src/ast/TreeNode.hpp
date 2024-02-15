#ifndef TREENODE_H
#define TREENODE_H

#include <iostream>
#include <vector>
#include <string>
#include "../parser/Symbole.hpp"



using namespace std;    
class TreeNode {
    public :
        string str;
        Symbole symbole;
        vector<TreeNode*> fils; //liste des noeuds fils, permet de faire un arbre n-aire
        TreeNode* pere;
        int id;

        TreeNode(string s = "", TreeNode* n = nullptr){//donne ces valeurs par défaut si un paramètre est manquant dans la création d'un TreeNode
            str = s;
            pere = n;
        }; 
};

void printTree(TreeNode* node); // affiche le parcours en DFS Preorder Traversal
void ajoutNode(TreeNode* ajout);
void ajoutkNode(vector<TreeNode*>& fils);
TreeNode* creePere(vector<TreeNode*>& fils, string str);
void ajoutNode(TreeNode* ajout, TreeNode* pere);
#endif