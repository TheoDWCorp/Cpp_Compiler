#ifndef GRAMMAIRE_CLASSES
#define GRAMMAIRE_CLASSES

#include <vector>
#include <unordered_set>
#include <unordered_map>
#include <string>
#include <iostream>

using namespace std;

// un automate est une liste d'états
// un état contient une map avec comme clés des non terminaux et comme valeurs des listes d'items
// un item contient une liste d'elements, un indice qui correspond à l'avancement (comme un marqueur) et contient un ensemble de terminaux (contexte)
// un element représente un terminal ou un non terminal

class Element { // terminal ou non terminal
    public:
        string value;
        bool is_terminal; // true -> terminal, false -> non terminal

        Element(string value, bool is_terminal) {
            this->value=value;
            this->is_terminal=is_terminal;
        }

        Element() {} // pour pouvoir creer des transitions (Element cost qui est un paramètre de Transition() fait un appel au constructeur de la classe Element donc il en faut un sans paramètres)
};

bool comparaison_elements(Element& A, Element& B);

bool comparaison_liste_elements(vector<Element>& A, vector<Element>& B);



class Item {
    public:
        vector<Element> liste_elements;
        int index;
        unordered_set<string> contexte; // ensemble de terminaux
        int id_reduction;

        Item(vector<Element> liste_elements, int index, unordered_set<string> contexte, int id_reduction) {
            this->liste_elements=liste_elements;
            this->index=index;
            this->contexte=contexte;
            this->id_reduction=id_reduction;
        }
};



class Etat {
    public:
        unordered_map<string, vector<Item>> map_items; // les clés sont des non terminaux

        Etat(unordered_map<string, vector<Item>> map_items) {
            this->map_items=map_items;
        }

        Etat() {}
};

void show_etat(Etat& etat);



class Transition { // transition entre deux états (sources et destinations sont les indices des états dans l'automate (liste d'états))
    public:
        int source;
        int destination;
        string cost; // element value

        Transition(int source, int destination, string cost) {
            this->source=source;
            this->destination=destination;
            this->cost=cost;
        }
};

void show_transitions(vector<Transition> liste_transitions);



class Reduction {
    public:
        string non_terminal;
        vector<Element> liste_elements;

        Reduction(string non_terminal, vector<Element> liste_elements) {
            this->non_terminal=non_terminal;
            this->liste_elements=liste_elements;
        }
};

#endif