#include <iostream>
#include <fstream>
#include <string>
#include <regex>

using namespace std;

int main(int argc, char* argv[]) {


    if (!argv[1]) {
        cout << "Erreur, merci d'indiquer un nom ou chemin du fichier à traiter" << endl;
        return 1;
    }

    string fileName (argv[1]);
    ifstream sourceFile(fileName);
    
    if (!sourceFile) {
        cout << "Impossible d'ouvrir le fichier source." << endl;
        return 1;
    }

    string scannedCode;

    regex commentRegex("--.*"); //Commentaire (une ligne)
    regex blockStartRegex("/\\*.*"); //Début block commentaire et ce qu'il suit
    regex blockEndRegex(".*\\*/"); //Fin block commentaire et ce qui le précède
    regex spaceRegex("\\s+"); //Espaces

    bool block = false;

    string line;
    while (getline(sourceFile, line)) {

        if (regex_search(line, blockStartRegex)) {
            block = true; //on commence un block
            line = regex_replace(line, blockStartRegex, ""); //on supprime le début du block en gardant le reste de la ligne
        }
        else if (regex_search(line, blockEndRegex)) {
            block = false; //on finit un block
            line = regex_replace(line, blockEndRegex, ""); //on supprime la fin du block en gardant le reste de la ligne
        }
        else if (block) {
            line = "\n"; //on supprime la ligne si on est dans un block (pas dans le cas de début ou de fin de block)
        }
        line = regex_replace(line, commentRegex, "");
        line = regex_replace(line, spaceRegex, " ");

        scannedCode += line + "\n";
    }

    sourceFile.close();

    if (!argv[2]) {
        ofstream outFile("scanned.txt");
        outFile << scannedCode;
    }
    else {
        string targetPath (argv[2]);
        ofstream outFile(targetPath);
        outFile << scannedCode;
    }

    return 0;
}
