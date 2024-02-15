TableDesSymboles_test.o : TableDesSymboles_test.cpp TableDesSymboles.hpp Identifier.hpp
	g++ -Wall -c TableDesSymboles_test.cpp

TableDesSymboles_test : TableDesSymboles_test.o
	g++ -Wall TableDesSymboles_test.o -o TableDesSymboles_test

clean :
	rm -f TreeNode TreeNode.o TreeNode_test.o TableDesSymboles_test TableDesSymboles_test.o TableDesSymboles.o
