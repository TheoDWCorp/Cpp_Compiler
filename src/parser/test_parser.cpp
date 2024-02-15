#include <iostream>
#include <vector>
#include "parser.hpp"
#include "../lex/lexeur.hpp"
#include "../tds/TableDesSymboles.hpp"
#include "../table_analyse/table_analyse.hpp"
#include "../ast/TreeNode.hpp"
#include "../token/Token.hpp"
#include "../ast/Visualisation.hpp"
#include "../ast/ast.hpp"


int main(int argc,char* argv []){
    //recup de la liste des tokens
    TableDesSymboles* table = new TableDesSymboles();

    vector<Token*> tokens= lexeur("../test.adb",false,false,table,"", false);

    //recup de la table d'analyse
    vector<vector<string>> table_analyse = get_table_analyse("../table_analyse/table_analyse.csv");
    TreeNode* parseTree = parser(tokens,table_analyse,false);

    parcoursEnLargeur(parseTree);//modifie id et symbole.representation aussi
    TreeNode* ast = new TreeNode("ast");
    ast->symbole = parseTree->symbole;
    foo(parseTree,ast);
    parcoursEnLargeur_ast(ast);
    return 0;
}