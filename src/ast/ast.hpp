#ifndef AST_HPP
#define AST_HPP

TreeNode* parseToAst(TreeNode* parseTree,bool debug);
bool isVisible(string repr);
void foo(TreeNode* node_p,TreeNode* pere_ast);
void parcoursEnLargeur_ast(TreeNode* root);
void foo_expr(TreeNode* node_p,TreeNode* pere_ast);

#endif // AST_HPP
