#include "grammaire_classes.hpp"

bool comparaison_elements(Element& A, Element& B) {
    return A.value==B.value&&A.is_terminal==B.is_terminal;
}

bool comparaison_liste_elements(vector<Element>& A, vector<Element>& B) {
    if (A.size()!=B.size()) return false;

    for (int i=0; i<A.size(); i++) {
        if (!comparaison_elements(A[i], B[i])) return false;
    }

    return true;
}


void show_etat(Etat& etat) {
    for (auto x:etat.map_items) {
        cout << x.first << " : \n";
        for (auto item:x.second) {
            for (int i=0; i<item.liste_elements.size(); i++) {
                if (i==item.index) cout << "•";
                cout << item.liste_elements[i].value;
            }
            if (item.index==item.liste_elements.size()) cout << "•";
            cout << "  [ ";
            for (auto element:item.contexte) {
                cout << element << " ";
            }
            cout << "]" << "\n";
        }
        cout << "\n";
    }
    cout << "\n\n";
}




void show_transitions(vector<Transition> liste_transitions) {
    for (auto transition:liste_transitions) {
        cout << transition.source << " " << transition.destination << " " << transition.cost << "\n";
    }
    cout << "\n\n";
}