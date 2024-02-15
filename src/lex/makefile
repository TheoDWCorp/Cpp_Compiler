CC =g++

bin = test_lexeur 
src = lexique.cpp lexeur.cpp
header = ../tds/TableDesSymboles.hpp

%.o : %.cpp 
	$(CC) -c $^ -o $@

$(bin) : $(src:%.cpp=%.o) $(bin:%=%.o) $(header)
	$(CC) $^ -o $@

clean : 
	@rm -f $(bin)
	@rm -f *.o