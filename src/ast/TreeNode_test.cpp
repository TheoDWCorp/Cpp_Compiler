#include <iostream>
#include <vector>
#include <string>
#include "TreeNode.hpp"


using namespace std;


int main(){
    //ETAPE 1 : CREER UN ARBRE ET L'AFFICHER
    cout << "ETAPE1 TEST \n";
    TreeNode* n1 = new TreeNode("a");
    TreeNode* n2 = new TreeNode("b",n1);
    TreeNode* n3 = new TreeNode("c",n1);
    TreeNode* n4 = new TreeNode("d",n1);
    TreeNode* n6 = new TreeNode("f",n2);
    TreeNode* n7 = new TreeNode("g",n2);
    TreeNode* n8 = new TreeNode("h",n4);
    TreeNode* n9 = new TreeNode("i",n4);
    vector<TreeNode*> v1(3);
    vector<TreeNode*> v2(2);
    vector<TreeNode*> v3(2);
    v1[0] = n2;
    v1[1] = n3;
    v1[2] = n4;
    v2[0] = n6;
    v2[1] = n7;
    v3[0] = n8;
    v3[1] = n9;
    n1->fils = v1;
    n2->fils = v2;
    n4->fils = v3;
    printTree(n1);
    cout << "\n";

    //ETAPE 2 : AJOUTER UNE BRANCHE ET AFFICHER L'ARBRE POUR VERIFIER
    cout << "ETAPE2 TEST \n";
    TreeNode* n5 = new TreeNode("e",n2);
    ajoutNode(n5);
    printTree(n1);
    cout << "\n";


    // ETAPE 3 : AJOUTER PLUSIEURS BRANCHES ET AFFICHER L'ARBRE POUR VERIFIER
    cout << "ETAPE3 TEST \n";
    TreeNode* n10 = new TreeNode("z",n3);
    TreeNode* n11 = new TreeNode("y",n8);
    TreeNode* n12 = new TreeNode("x",n8);
    vector<TreeNode*> v(3);
    v[0] = n10;
    v[1] = n11;
    v[2] = n12;
    ajoutkNode(v);
    printTree(n1);
    cout << "\n";


    //ETAPE 4 : AJOUTER UN PERE A PLUSIEURS FILS ET AFFICHER LE SOUS ARBRE DE CE PERE
    cout << "ETAPE 4 TEST \n"; 
    TreeNode* a = creePere(v,"ab");
    printTree(a);


    return 0;
}