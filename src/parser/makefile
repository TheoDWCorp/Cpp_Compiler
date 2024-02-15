CC =g++

bin = test_parser
src = parser.cpp ../ast/TreeNode.cpp ../table_analyse/table_analyse.cpp foo_parser.cpp ../lex/lexeur.cpp ../lex/lexique.cpp ../ast/Visualisation.cpp ../ast/ast.cpp

%.o : %.cpp 
	$(CC) -c $^ -o $@

$(bin) : $(src:%.cpp=%.o) $(bin:%=%.o) $(header)
	$(CC) $^ -o $@

clean : 
	@rm -f $(bin)
	@rm -f *.o