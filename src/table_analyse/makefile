CC = g++

bin = grammaire_sujet_modifier ../lex/lexique.o ../lex/lexeur.o create_automate chrono 

%.o : %.cpp 
	$(CC) -c $^ -o $@

grammaire_sujet_modifier: grammaire_sujet_modifier.o ../lex/lexique.o ../lex/lexeur.o
	$(CC) $^ -o $@

create_automate: create_automate.o grammaire_classes.o automate.o
	$(CC) $^ -o $@

chrono: chrono.o table_analyse.o
	$(CC) $^ -o $@

all: $(bin)


clean : 
	@rm -f $(bin)
	@rm -f *.o