#include <iostream>
#include <vector>
#include <string>
#include "Identifier.hpp"

using namespace std;

#ifndef TDS_H
#define TDS_H


class TableDesSymboles{
    public :
    vector<Identifier*> contenu;

    TableDesSymboles(){
        vector<Identifier*> table(0);
        contenu = table;
    }

    void ajoutIdf(Identifier* idf){
        contenu.push_back(idf); //ajoute l'identifiant à la fin de la table
    };

    void ajoutkIdf(TableDesSymboles* idfs){
        int n = idfs->contenu.size();
        for (int i=0; i<n; i++){
            ajoutIdf(idfs->contenu[i]);
        }
    };

    void printTable(){
        int n = contenu.size();
        for (int i=0; i<n; i++){
            cout << "(" << contenu[i]->idf << ";" << i << ") \n";//affiche les éléments avec la syntaxe suivante (nom,indice_lexical)
        }
    };

    Identifier* getIdf(int indice){
        return contenu[indice];
    };

    int getIndice(Identifier* idf){
        int n = contenu.size();
        for (int i=0; i<n; i++){
            if (contenu[i] == idf){
                return i;
            }
        }
        return -1;
    };

    void destroyTable(){
        contenu.clear();//vide la table de tous ses éléments
    };

}; 






#endif