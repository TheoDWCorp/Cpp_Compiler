#include <iostream>
#include <vector>
#include <string>
#include "TreeNode.hpp"

using namespace std;


void printTree(TreeNode* node){//DFS Preorder Traversal 
//cette fonction ne print que le string contenu par le noeud et pas le noeud entier
    cout << node->str << "\n";
    int n = node->fils.size();
    if (n!=0){
        for (int i=0;i<n;i++){
            printTree(node->fils[i]);
        }
    }
}


void ajoutNode(TreeNode* ajout){
    ajout->pere->fils.push_back(ajout);//ajout->pere->fils permet d'accéder à la liste des noeuds "freres" d'ajout
}

void ajoutNode(TreeNode* ajout, TreeNode* pere){
    ajout->pere = pere;
    ajout->pere->fils.push_back(ajout);//ajout->pere->fils permet d'accéder à la liste des noeuds "freres" d'ajout
}

void ajoutkNode(vector<TreeNode*>& ajouts){
    int n = ajouts.size();
    for (int i=0; i<n; i++){
        ajoutNode(ajouts[i]);
    }
}

TreeNode* creePere(vector<TreeNode*>& fils, string str){
    TreeNode* father = new TreeNode(str);
    father->fils = fils;
    for (int i=0; i<(int)fils.size(); i++){
        fils[i]->pere = father; 
    }
    return father;
}

