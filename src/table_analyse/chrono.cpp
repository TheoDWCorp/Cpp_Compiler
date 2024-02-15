#include <iostream>
#include <vector>
#include <string>
#include <chrono>
#include "table_analyse.hpp"

int main() {
    clock_t start, end;

    start = clock();
    vector<vector<string>> table_analyse = get_table_analyse("table_analyse.csv");
    end = clock();
    cout << "time : " << (double)(end-start)/CLOCKS_PER_SEC << "\n";
    //save_table_analyse("table_analyse_test.csv", table_analyse);


    //vector<Reduction> liste_reductions = get_liste_reduction("liste_reductions.txt", '#', '&');
    //save_liste_reductions("liste_reductions_test.txt", liste_reductions, '#', '&');

    return 0;
}