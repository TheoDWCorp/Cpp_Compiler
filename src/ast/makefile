#compile et exécute en écrivant "make all" dans le terminal en étant dans le répertoire src/

TreeNode.o : TreeNode.cpp 
	g++ -c TreeNode.cpp
ast.o : ast.cpp 
	g++ -c ast.cpp

TreeNode_test.o : TreeNode_test.cpp 
	g++ -c TreeNode_test.cpp

TreeNode : TreeNode.o TreeNode_test.o
	g++ TreeNode.o TreeNode_test.o -o TreeNode

Visualisation.o : Visualisation.cpp TreeNode.hpp
	g++ -Wall -c Visualisation.cpp

clean :
	rm -f TreeNode TreeNode.o TreeNode_test.o

