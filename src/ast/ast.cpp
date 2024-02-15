#include <iostream>
#include <fstream>
#include <string>
#include <queue>
#include "TreeNode.hpp"
#include "ast.hpp"



TreeNode* parseToAst(TreeNode* parseTree,bool debug){
    queue<TreeNode*> toVisit;
    toVisit.push(parseTree);
    TreeNode* ast = new TreeNode("ast");

    while(!toVisit.empty()){
        TreeNode* current = toVisit.front();
        string repr = current->symbole.representation;
        if (repr=="ident"){
            if (debug){
                cout << "Found ident" << endl;
            }
            
        }
        else{
            if (debug){
                cout << "Found other" << endl;
            }
        }
        toVisit.pop();
        for (TreeNode* fils : current->fils){
            toVisit.push(fils);
        }

        
    }
    return parseTree;
}

bool isVisible(string repr){
    if (repr==";"){
        return false;
    }
    else if (repr==":"){
        return false;
    }
    else if (repr==".."){
        return false;
    }
    else if (repr==":="){
        return false;
    }
    else if (repr=="("){
        return false;
    }
    else if (repr==")"){
        return false;
    }
    else if (repr==","){
        return false;
    }
    else if (repr=="."){
        return false;
    }
    else if (repr=="include_statement+"){
        return false;
    }
    else if (repr=="ident_virgule+"){
        return false;
    }
    else if (repr=="instr+"){
        return false;
    }
    else if (repr=="expr6"){
        return false;
    }
    else if (repr=="param_points_virgule+"){
        return false;
    }
    else if (repr=="expr_virgule+"){
        return false;
    }
    else if (repr=="fichier'"){
        return false;
    }
    return true;
}


void foo(TreeNode* node_p,TreeNode* pere_ast){
    if (isVisible(node_p->symbole.representation)){
        //copie de node_p dans node_ast
        TreeNode* node_ast = new TreeNode(node_p->str,pere_ast);
        node_ast->symbole = node_p->symbole;
        node_ast->id = node_p->id;
        //ajout de node_ast dans pere_ast
        pere_ast->fils.push_back(node_ast);
        if (node_p->symbole.representation == "expr"){
            for (TreeNode* fils : node_p->fils){
                foo_expr(fils,node_ast);
            }   
        }else{
            for (TreeNode* fils : node_p->fils){
                foo(fils,node_ast);
            }   
        }
        
    }
    else{
        for (TreeNode* fils : node_p->fils){
            foo(fils,pere_ast);
        }
    }
}

void foo_expr(TreeNode* node_p,TreeNode* pere_ast){
    if (node_p->symbole.representation == "expr6"){
        foo(node_p,pere_ast);
    }
    else{
        int node_p_size = node_p->fils.size();
        switch (node_p_size)
        {
            case 1:
            {
                foo_expr(node_p->fils[0],pere_ast);   
                break;
            }
            case 2:
            {
                cout <<"impopssible"<<endl;
                break;
            }
            case 3:
            {   //on remonte l'op et on appelle sur les fg fd
                TreeNode* node_ast = new TreeNode(node_p->fils[1]->str,pere_ast);
                node_ast->symbole = node_p->fils[1]->symbole;
                node_ast->id = node_p->fils[1]->id;
                pere_ast->fils.push_back(node_ast);

                foo_expr(node_p->fils[0],node_ast);
                foo_expr(node_p->fils[2],node_ast);
                break;
            }
            case 4:
            {
                if (node_p->fils[0]->symbole.representation == "not"){
                    TreeNode* node_ast = new TreeNode(node_p->fils[0]->str,pere_ast);
                    node_ast->symbole = node_p->fils[0]->symbole;
                    node_ast->id = node_p->fils[0]->id;
                    pere_ast->fils.push_back(node_ast);

                    foo_expr(node_p->fils[2],node_ast);
                }
                else{
                    foo_expr(node_p->fils[0],pere_ast);
                    TreeNode* node_ast = new TreeNode(node_p->fils[1]->str,pere_ast);
                    node_ast->symbole = node_p->fils[1]->symbole;
                    node_ast->id = node_p->fils[1]->id;
                    pere_ast->fils.push_back(node_ast);
                    TreeNode* node_ast2 = new TreeNode(node_p->fils[2]->str,pere_ast);
                    node_ast2->symbole = node_p->fils[2]->symbole;
                    node_ast2->id = node_p->fils[2]->id;
                    pere_ast->fils.push_back(node_ast2);
                    foo_expr(node_p->fils[3],pere_ast);
                
                }
            }
            default:
            {
                break;
            }
        }
            
    }
}

void parcoursEnLargeur_ast(TreeNode* root) {
    string filename = "ast.puml";
    ofstream out(filename);
    out << "@startuml ast" << endl;
    out << "hide methods" << endl;
    out << "hide attribute" << endl;
    out << "hide circle" << endl;

    if (root == nullptr) return;

    queue<TreeNode*> queue;
    queue.push(root);
    while (!queue.empty()) {
        TreeNode* current = queue.front();
        queue.pop();

        out << "class \""<<current->id<<" : " << current->symbole.representation << "\"{}"<< endl;
        if (current->pere != nullptr) {
            out << "\""<<current->pere->id<<" : " <<current->pere->symbole.representation << "\""<< " --> " << "\""<<current->id<<" : "<< current->symbole.representation << "\""<< endl;
        }

        for (TreeNode* child : current->fils) {
            queue.push(child);
        }
        
    }

    out << "@endmindmap" << endl;
    out.close();
}