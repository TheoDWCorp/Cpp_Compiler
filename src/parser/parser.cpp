#include <iostream>
#include <vector>
#include <fstream>
#include <sstream>

#include "../ast/TreeNode.hpp"
#include "../table_analyse/table_analyse.hpp"
#include "../token/Token.hpp"
#include "foo_parser.hpp"
#include "parser.hpp"
#include "../ast/Visualisation.hpp"

using namespace std;


TreeNode* parser(vector<Token*> tokens,vector<vector<string>> tableAnalyse,bool debug){

    // parse
    vector<Symbole> stack_symbole;
    vector<int> stack_state;
    
    stack_state.push_back(0);

    //construction de l'arbre
    TreeNode* current_father = new TreeNode();
    Symbole symbole_f = Symbole();
    symbole_f.is_terminal=false;
    symbole_f.representation = "papa";

    int i=0;
    while (i<tokens.size()+1){
        

        
        if (i>=tokens.size()){
            if (debug){
                cout<<"fin de la chaine de token"<<endl;
            }
            //fin de la chaine de token
            string toDo = getAction(tableAnalyse,"$",stack_state.back());
            while (toDo!="r0"){
                string toDo = getAction(tableAnalyse,"$",stack_state.back());
                int num_reduction = stoi(toDo.substr(1));
                //récupération de la taille de la réduction 
                int size_reduction = get_length_reduction(num_reduction);
                if (debug){
                    cout<<size_reduction<<" la bas "<<num_reduction<< endl;
                }
                if (debug){
                    cout<<"toDO : "<<toDo<<endl;
                    cout<<"index dans tokens : "<<i<<endl;
                    cout<<"tokens :"<<endl;
                    int j=0;
                    for (Token* token:tokens){
                        if (j==i){
                            cout<<"| ";
                        }
                        cout<<token->index<<" ";
                        j++;
                    }
                    cout<<endl;
                    cout<<"stack_symbole :"<<endl;
                    for (Symbole symbole:stack_symbole){
                        cout<<symbole.representation<<" ";
                    }
                    cout<<endl;
                    cout<<"stack_state :"<<endl;
                    for (int state:stack_state){
                        cout<<state<<" ";
                    }   
                    cout<<endl<<endl<<endl;
                }
                //suprr des symboles réduit
                for (int j=0;j<size_reduction;j++){
                    stack_state.pop_back();
                    stack_symbole.pop_back();
                }
                //ajout de resultat de la reduction
                Symbole symbole_res = Symbole();

                symbole_res.is_terminal=false;
                symbole_res.representation = get_res_reduction(num_reduction);
                stack_symbole.push_back(symbole_res);
                
                if (stack_state.size()>1){
                    //add le nouveau state
                    string state = getAction(tableAnalyse,symbole_res.representation,stack_state.back());
                    stack_state.push_back(stoi(state.substr(1)));
                }
                
                //créer l'arbre
                vector<TreeNode*> son;
                for (int j=0;j<size_reduction;j++){//retirer les symboles de la reduction et les ajouters dans son
                    son.insert(son.begin(), current_father->fils.back());
                    current_father->fils.pop_back();
                }
                //ajout du nouveau symbole dans curent_father
                TreeNode* pere = creePere(son,"");
                pere->symbole= symbole_res;
                pere->pere = current_father;
                current_father->fils.push_back(pere);

                if (debug){
                    cout<<"fin r"<<endl;
                    cout<<"stack_symbole :"<<endl;
                    for (Symbole symbole:stack_symbole){
                        cout<<symbole.representation<<" ";
                    }
                    cout<<endl;
                    cout<<"stack_state :"<<endl;
                    for (int state:stack_state){
                        cout<<state<<" ";
                    }   
                    cout<<endl<<"------------"<<endl<<endl;
                }
                if (stack_state.size()<=1){
                    return current_father;
                }

            }


            if (debug){
                    cout<<"fin de la chaine de token"<<endl; 
                    cout<<"tokens :"<<endl;
                    int j=0;
                    for (Token* token:tokens){
                        cout<<token->index<<" ";
                    }
                    cout<<" |"<<endl;
                    cout<<"stack_symbole :"<<endl;
                    for (Symbole symbole:stack_symbole){
                        cout<<symbole.representation<<" ";
                    }
                    cout<<endl;
                    cout<<"stack_state :"<<endl;
                    for (int state:stack_state){
                        cout<<state<<" ";
                    }   
                    cout<<endl<<endl<<endl;
                }
            //fin de l'analyse
            return current_father;
        }
        // check la table d'analyse
        string element = to_string(tokens[i]->index);
        string toDo = getAction(tableAnalyse,element,stack_state.back());
        
        switch (toDo[0]) {
            case 'd':
            {
                if (debug){
                    cout<<"toDO : "<<toDo<<endl;
                    cout<<"index dans tokens : "<<i<<endl;
                    cout<<"tokens :"<<endl;
                    int j=0;
                    for (Token* token:tokens){
                        if (j==i){
                            cout<<"| ";
                        }
                        cout<<token->index<<" ";
                        j++;
                    }
                    cout<<endl;
                    cout<<"stack_symbole :"<<endl;
                    for (Symbole symbole:stack_symbole){
                        cout<<symbole.representation<<" ";
                    }
                    cout<<endl;
                    cout<<"stack_state :"<<endl;
                    for (int state:stack_state){
                        cout<<state<<" ";
                    }   
                    cout<<endl<<endl<<endl;
                }

                // LECTURE

                //              continuer de parser
                //ajout du state
                int state = stoi(toDo.substr(1)); // Get substring excluding the first character
                stack_state.push_back(state);

                //ajout du symbole

                Symbole symbole = Symbole();

                symbole.is_terminal=true;
                symbole.token = tokens[i];
                symbole.representation = to_string(symbole.token->index);
                stack_symbole.push_back(symbole);

                //                 créer l'arbre
                
                ajoutNode(create_node(symbole),current_father);

                //  incrément de l'index de la liste de token a parcourir
                i++;
                if (debug){
                    cout<<"fin d"<<endl;
                    cout<<"stack_symbole :"<<endl;
                    for (Symbole symbole:stack_symbole){
                        cout<<symbole.representation<<" ";
                    }
                    cout<<endl;
                    cout<<"stack_state :"<<endl;
                    for (int state:stack_state){
                        cout<<state<<" ";
                    }   
                    cout<<endl<<"------------"<<endl<<endl;
                }
                break;


            }
            case 'r':
                {
                if (debug){
                    cout<<"toDO : "<<toDo<<endl;
                    cout<<"index dans tokens : "<<i<<endl;
                    cout<<"tokens :"<<endl;
                    int j=0;
                    for (Token* token:tokens){
                        if (j==i){
                            cout<<"| ";
                        }
                        cout<<token->index<<" ";
                        j++;
                    }
                    cout<<endl;
                    cout<<"stack_symbole :"<<endl;
                    for (Symbole symbole:stack_symbole){
                        cout<<symbole.representation<<" ";
                    }
                    cout<<endl;
                    cout<<"stack_state :"<<endl;
                    for (int state:stack_state){
                        cout<<state<<" ";
                    }   
                    cout<<endl<<endl<<endl;
                }

                // REDUCTION

                //continuer de parser

                int num_reduction = stoi(toDo.substr(1));
                //récupération de la taille de la réduction 
                int size_reduction = get_length_reduction(num_reduction);
                //suprr des symboles réduit
                for (int j=0;j<size_reduction;j++){
                    stack_state.pop_back();
                    stack_symbole.pop_back();
                }
                //ajout de resultat de la reduction
                Symbole symbole_res = Symbole();

                symbole_res.is_terminal=false;
                symbole_res.representation = get_res_reduction(num_reduction);
                stack_symbole.push_back(symbole_res);

                //add le nouveau state
                string state = getAction(tableAnalyse,symbole_res.representation,stack_state.back());
                stack_state.push_back(stoi(state.substr(1)));
                

                //créer l'arbre

                vector<TreeNode*> son;
                for (int j=0;j<size_reduction;j++){//retirer les symboles de la reduction et les ajouters dans son
                    son.insert(son.begin(), current_father->fils.back());
                    current_father->fils.pop_back();
                }
                //ajout du nouveau symbole dans curent_father
                TreeNode* pere = creePere(son,"");
                pere->symbole= symbole_res;
                pere->pere = current_father;
                current_father->fils.push_back(pere);

                if (debug){
                    cout<<"fin r"<<endl;
                    cout<<"stack_symbole :"<<endl;
                    for (Symbole symbole:stack_symbole){
                        cout<<symbole.representation<<" ";
                    }
                    cout<<endl;
                    cout<<"stack_state :"<<endl;
                    for (int state:stack_state){
                        cout<<state<<" ";
                    }   
                    cout<<endl<<"------------"<<endl<<endl;
                }
                if (toDo=="r0"){
                    //fin de l'analyse
                    return current_father;
                }
                break;
                }


            default:
            {
                if (debug){
                    cout<<"erreur"<<endl;   
                    cout<<"toDO : "<<toDo<<endl;
                    cout<<"index dans tokens : "<<i<<endl;
                    cout<<"tokens :"<<endl;
                    int j=0;
                    for (Token* token:tokens){
                        if (j==i){
                            cout<<"| ";
                        }
                        cout<<token->index<<" ";
                        j++;
                    }
                    cout<<endl;
                    cout<<"stack_symbole :"<<endl;
                    for (Symbole symbole:stack_symbole){
                        cout<<symbole.representation<<" ";
                    }
                    cout<<endl;
                    cout<<"stack_state :"<<endl;
                    for (int state:stack_state){
                        cout<<state<<" ";
                    }   
                    cout<<endl;
                }
                


                cout<<"Erreur dans la chaine analysé"<<endl<<"ligne "<<tokens[i]->line+1<<" : "<<endl;
                //impression de la ligne en question : 
                ifstream inputFile;
                inputFile.open("../test.adb");
                if (!inputFile.is_open()) {
                    cout << "le ficher src ne s'ouvre pas" << endl;
                }
                string line;
                string error_ligne;
                int k=0;
                while (getline(inputFile, line)) {
                    if (k==tokens[i]->line)
                        error_ligne = line;
                    k++;
                }
                inputFile.close();

                cout<<error_ligne<<endl;
                for (int j=0;j<tokens[i]->nb_character-1;j++){
                    cout<<" ";
                }
                cout<<"^"<<endl;
                
                //récupération des charactères attendu :
                cout<<"token(s) attendu  : "; 
                for (string str:getExpected(tableAnalyse,stack_state.back())){
                    if (getKeyWord(stoi(str))!="r"){
                        cout<<getKeyWord(stoi(str))<<" ";
                    }
                    else{
                        cout<<str<<" ";
                    }
                }
                cout<<endl;

                return current_father;
                
                break;
            }
        }
        
        
    }
    //retourner l'arbre dans la liste si il existe
    return current_father;
}

TreeNode* create_node(Symbole symbole){
    TreeNode* temp = new TreeNode();
    temp->symbole=symbole;
    return temp;
}