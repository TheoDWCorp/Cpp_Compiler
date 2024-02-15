#include <iostream>
#include <vector>
#include <string>
#include "Identifier.hpp"
#include "TableDesSymboles.hpp"

using namespace std;

int main(){
    //TEST 1 : Créer une tds et l'afficher
    cout << "TEST 1 : \n";
    TableDesSymboles* table = new TableDesSymboles();
    table->printTable();

    //TEST 2 : Ajouter un élément à cette table et l'afficher
    cout << "\n" << "TEST 2 : \n";
    Identifier* i = new Identifier("x",2);
    table->ajoutIdf(i);
    table->printTable();
    cout << "\n" << "TEST 3 :\n";

    //TEST 3 : Ajouter plusieurs éléments à cette table et l'afficher
    TableDesSymboles* idfs = new TableDesSymboles();
    Identifier* i1 = new Identifier("y",4);
    Identifier* i2 = new Identifier("tmp",5);
    Identifier* i3 = new Identifier("i",5);
    idfs->ajoutIdf(i1);
    idfs->ajoutIdf(i2);
    idfs->ajoutIdf(i3);
    table->ajoutkIdf(idfs);
    table->printTable();

    //TEST 4 : Chercher un élément de la table avec son indice, et l'afficher
    cout << "\n" << "TEST 4 : \n";
    printIdf(table->getIdf(3));

    //TEST 5 : Chercher l'indice d'un élément de la table avec l'élement, et voir que c'est le bon
    cout << "\n" << "TEST 5 : \n";
    cout << "Indice de y dans la table : " << table->getIndice(i1) << "\n";


    //TEST 6 : Vider la table et l'afficher pour s'en assurer
    cout << "\n" << "TEST 6 : \n";
    table->destroyTable();
    table->printTable();

    return 0;
}