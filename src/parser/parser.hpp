#ifndef PARSER_HPP
#define PARSER_HPP

#include "Symbole.hpp"
#include "../token/Token.hpp"
#include "../ast/TreeNode.hpp"


TreeNode* parser(vector<Token*> tokens,vector<vector<string>> tableAnalyse,bool debug);
TreeNode* create_node(Symbole symbole);


#endif // PARSER_HPP
