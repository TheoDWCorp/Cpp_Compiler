#include <iostream>
#include <string>
#include <regex> 
#include <unordered_map> 
#include <unordered_set>
#include <vector>

#include "../tds/Identifier.hpp"

#include "../token/Token.hpp"
#include "../token/Keyword.hpp"
#include "../token/Operateur.hpp"
#include "../token/Constante.hpp"
#include "../token/BoolConstante.hpp"
#include "../token/CharConstante.hpp"
#include "../token/FloatConstante.hpp"
#include "../token/IntConstante.hpp"
#include "../token/Identifiant.hpp"
#include "../token/StringConstante.hpp"

#include "../tds/TableDesSymboles.hpp"



using namespace std; 


int lexique(string lexeme,bool* isIn){
    //modifie isIn en True si lexeme est dans le lexique, e, False sinon
    //return l'indice du token si isIn
    //return -1 sinon

    unordered_map<string, int> lexique; 

    //keyword
    lexique["and"]=0;
    lexique["begin"]=1;
    lexique["else"]=2;
    lexique["elsif"]=3;
    lexique["end"]=4;
    lexique["for"]=5;
    lexique["function"]=6;
    lexique["if"]=7;
    lexique["in"]=8;
    lexique["is"]=9;
    lexique["loop"]=10;
    lexique["not"]=11;
    lexique["null"]=12;
    lexique["or"]=13;
    lexique["out"]=14;
    lexique["procedure"]=15;
    lexique["record"]=16;
    lexique["rem"]=17;
    lexique["return"]=18 ;
    lexique["reverse"]=19;
    lexique["then"]=20;
    lexique["type"]=21;
    lexique["use"]=22;
    lexique["while"]=23;
    lexique["with"]=24;

    //opérateur
    lexique["+"]=30;
    lexique["-"]=31;
    lexique["/"]=32;
    lexique["*"]=33;
    lexique["<"]=34;
    lexique[">"]=35;
    lexique["="]=36;
    lexique["/="]=37;
    lexique["<="]=38;
    lexique[">="]=39;
    lexique[":="]=40;

    //séparateur
    lexique[":"]=41;
    lexique[";"]=42;
    lexique["("]=43;
    lexique[")"]=44;
    lexique["."]=45;
    lexique[","]=46;
    lexique["'"]=47;
    

    *isIn = lexique.find(lexeme)!=lexique.end();
    if (*isIn)
        return lexique[lexeme];
    else    
        return -1;   
}
bool isSeparator(char e){
    unordered_set<char> sep;
    string sep_l = ";= :+-*/,()[]{}<>\"'.";
    for (char c:sep_l){
        sep.insert(c);

    }
    return sep.find(e)!=sep.end();
}

bool isBool(string lexeme,bool* isIn){
    //modifie isIn si lexeme est true ou false
    //return la valeur si isIn
    //return false sinon
    if (lexeme == "true"){
        *isIn=true;
        return true;
    }
    else if (lexeme == "false"){
        *isIn=true;
        return false;
    }
    else 
        return false;
}

char getLexeme(string lexeme) {
    //retourne le lexeme sans les quotes
    return lexeme[1];
}

Token* determinationToken(string lexeme,int ligne,int nb_character,TableDesSymboles* table){
    bool isIn;
    int token_index;
    token_index=lexique(lexeme,&isIn);
    if (isIn){
        if (token_index>=30 && token_index<=40){
            return new Operateur(token_index,ligne,nb_character);
        }
        return new Keyword(token_index,ligne,nb_character);
    }
    bool valeur = isBool(lexeme,&isIn);
    if (isIn){
        
        return new BoolConstante(50,valeur,ligne,nb_character);
    }
    regex charConst("'[A-Za-z]'");
    if (regex_match(lexeme,charConst)){
        if (lexeme.size()!=3)
            return new CharConstante(50,getLexeme(lexeme),ligne,nb_character);
        
        
        return new Keyword(100,ligne,nb_character);
    }
    regex floatConst("-?[0-9]+\\.[0-9]*");
    if (regex_match(lexeme,floatConst)){
        return new FloatConstante(50,stof(lexeme),ligne,nb_character);//le -'0' permet de convertir le char en int
    }

    regex intConst("-?[0-9]+");
    if (regex_match(lexeme,intConst)){

        return new IntConstante(50,stoi(lexeme) ,ligne,nb_character);
    }

    regex strConst("\"([^\"]*)\"");
    if (regex_match(lexeme,strConst)){
        string lex = lexeme.substr(1, lexeme.size() - 2);
        return new StringConstante(50,lex,ligne,nb_character); //Conversion de char en string
    }

    regex idf("[a-zA-Z]([a-zA-Z0-9]|_)*");
    if (regex_match(lexeme,idf)){
        //ajouter à la table de symbole 
        
        table->ajoutIdf(new Identifier(lexeme,ligne));
        int index_table = table->contenu.size()-1;//index de la table des symboles
        return new Identifiant(index_table,ligne,lexeme,55,nb_character);
    }
    return new Keyword(101,ligne,nb_character);
}
