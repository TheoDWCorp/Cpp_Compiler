#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <regex>
#include <vector>
#include "../token/Token.hpp"
#include "../token/Keyword.hpp"
#include "../token/Operateur.hpp"
#include "../token/Constante.hpp"
#include "../token/BoolConstante.hpp"
#include "../token/CharConstante.hpp"
#include "../token/FloatConstante.hpp"
#include "../token/IntConstante.hpp"
#include "../token/Identifiant.hpp"

#include "../tds/Identifier.hpp"
#include "../tds/TableDesSymboles.hpp"
#include "lexique.hpp"
#include "lexeur.hpp"



using namespace std;

vector<Token*> lexeur(string srcFile,bool outputLexeme, bool outputToken,TableDesSymboles* table, string path,bool bool_path){
//ouverture du fichier renseigné
    stringstream sourceFile;
    if (bool_path){
        sourceFile<<srcFile;
    }
    else{
        ifstream sourceFile_(srcFile);
        sourceFile<<sourceFile_.rdbuf();
        if (!sourceFile) {
            cout << "Impossible d'ouvrir le fichier " << srcFile<<endl;
            vector<Token*> token;
            return token;
    }


    }


//lecture du fichier
    //pour les tokens
    vector<Token*> tokens;
    

    //pour lire une ligne du texte
    string ligne;

    //pour délimiter les lexemes
    int pos,len;

    //pour garder les numéro de ligne (pour les erreurs)
    int numero_ligne=0;

    //pour stocké temporairement les lexemes
    string lexeme;


    bool isString=false;//permet de verifier qu'on est pas dans une chaine  de charactère
    bool isEqu=false;//permet de tester si on rencontre un opérateur à 2 charactère.
    bool isFloat=false;//permet de tester si on parse un float quand on rencontre . ou non;
    string equ = "/:<>";//les symboles des opérateurs à 2 char

    stringstream output;
    if (outputLexeme) output<<"LEXEMES\n"; // début de la partie Lexemes

    while (getline(sourceFile,ligne)){
        pos=0;len=0;
        for (char e:ligne){
            if (isFloat && (e!='.')){
                isFloat=false;
            }
            if (e == '\"' && not(isString)){//début de chaine de charactère
                isString=true;
                lexeme = ligne.substr(pos,len);
                if (lexeme != ""){
                    if (outputLexeme)
                        output<<lexeme<<endl;

                    tokens.push_back(determinationToken(lexeme,numero_ligne,pos,table));
                }

                pos=pos+len;
                len=0;
            }
            else if (e == '\"' && isString){//fin de chaine de charactère
                isString=false;
                lexeme = ligne.substr(pos,len+2);
                if (outputLexeme)
                    output<<lexeme<<endl;
                
                tokens.push_back(determinationToken(lexeme,numero_ligne,pos,table));

                pos=pos+len+2;
                len=0;
            }
            else if (e=='=' && isEqu){//cas d'un symbole à 2 séparateurs (:=)
                isEqu=false;
                lexeme = ligne.substr(pos,len+1);
                if (lexeme != ""){
                    if (outputLexeme)
                        output<<lexeme<<endl;
                        
                    tokens.push_back(determinationToken(lexeme,numero_ligne,pos,table));
                }
                pos=pos+len+1;
                len=0;
            }
            else if(equ.find(e) != string::npos && not(isString)){//cas d'un premier séparateurs pouvant être un symbole à 2 séparateurs
                isEqu=true;
                lexeme = ligne.substr(pos,len);
                if (lexeme != ""){
                    if (outputLexeme)
                        output<<lexeme<<endl;
                        
                    tokens.push_back(determinationToken(lexeme,numero_ligne,pos,table));
                }
                pos=pos+len;
                len=1;
            }
            else if (isFloat && e == '.'){
                len++;
                isFloat=false;
            }
            else if (isSeparator(e) && not(isString)){//cas d'un séparateurs
                lexeme = ligne.substr(pos,len);
                if (lexeme != ""){
                    if (outputLexeme)
                        output<<lexeme<<endl;
                        
                    tokens.push_back(determinationToken(lexeme,numero_ligne,pos,table));
                }

                pos=pos+len+1;
                len=0;
                lexeme = e;
                if (lexeme!= " "){
                    if (outputLexeme)
                        output<<lexeme<<endl;
                        
                    tokens.push_back(determinationToken(lexeme,numero_ligne,pos,table));
                }

            }

            else if (isEqu){//cas d'un charactère autre que = si on avait un separateurs avant
                isEqu=false;
                lexeme = ligne.substr(pos,len);
                if (lexeme != ""){
                    if (outputLexeme)
                        output<<lexeme<<endl;
                        
                    tokens.push_back(determinationToken(lexeme,numero_ligne,pos,table));
                }
                pos=pos+len;
                len=1;
            }
            else if (isdigit(e)){
                len++;
                isFloat = true;

            }
            else{//tout les autres cas
                len++;
            }
        }
        if (len>0){
            lexeme = ligne.substr(pos,len);
            if (outputLexeme)
                output<<lexeme<<endl;
                
            tokens.push_back(determinationToken(lexeme,numero_ligne,pos,table));
        }
        numero_ligne++;
    }

    if (outputLexeme) output<<"\n\n"; // fin de la partie Lexeme


    //récupération des cst négatives
    //avant un - :
    // +*/=<>
    //
    if (tokens.size()>2){
        vector<int> toErase;
        for (int i=0;i<tokens.size()-2;i++){
            if (tokens[i]->index==31){
                if (i>0){
                    if (tokens[i-1]->index>=30 && tokens[i-1]->index<=40){
                        if (tokens[i+1]->index==50){
                            if (tokens[i+1]->name=="float_constante"){
                                float val = dynamic_cast<FloatConstante*>(tokens[i+1])->value;
                                int ligne=tokens[i+1]->line;
                                int nb_char=tokens[i+1]->nb_character;
                                tokens[i+1]=new FloatConstante(50,-val,ligne,nb_char);
                                toErase.insert(toErase.begin(),i);
                            }
                            if (tokens[i+1]->name=="int_constante"){
                                int val = dynamic_cast<IntConstante*>(tokens[i+1])->value;
                                int ligne=tokens[i+1]->line;
                                int nb_char=tokens[i+1]->nb_character;
                                tokens[i+1]=new IntConstante(50,-val,ligne,nb_char);
                                toErase.insert(toErase.begin(),i);
                            }

                            

                        }
                    }
                }
                    
            }

            //recup les 'c'
            if (tokens[i]->index==47 && tokens[i+2]->index==47){
                int ligne;
                int nb_char;
                tokens[i+1]->line = ligne;

                tokens[i]->nb_character = nb_char;
                string idf = dynamic_cast<Identifiant*>(tokens[i+1])->idf;

                tokens[i] = new CharConstante(50,(char)idf[0],ligne,nb_char);
                toErase.insert(toErase.begin(),i+1);
                toErase.insert(toErase.begin(),i+2);
            }
            if (tokens[i]->index==55 && tokens[i+1]->index==45 && tokens[i+2]->index==55){
                int ligne;
                int nb_char;
                tokens[i+1]->line = ligne;
                tokens[i]->nb_character = nb_char;
                string idf1 = dynamic_cast<Identifiant*>(tokens[i])->idf;
                string idf2 = dynamic_cast<Identifiant*>(tokens[i+2])->idf;
                table->ajoutIdf(new Identifier(idf1+"."+idf2,ligne));
                int index_table = table->contenu.size()-1;
                tokens[i] = new Identifiant(index_table,ligne,idf1+"."+idf2,55,nb_char);
                toErase.insert(toErase.begin(),i+1);
                toErase.insert(toErase.begin(),i+2);
            }
            
        }
        for (int i:toErase){
        tokens.erase(tokens.begin()+i);
        }
    }    
    

    if (outputToken){
        cout << "TOKENS\n"; // début de la partie Tokens
        for (Token* t:tokens){
            t->printToken();
        }
        output << "\n\n"; // fin de la partie Tokens
    }
    if (outputLexeme||outputToken) {
        if (path=="") cout << output.rdbuf();
        else {
            ofstream output_file(path);
            output_file << output.rdbuf();
            output_file.close();
        }
    }
    return tokens;
}
