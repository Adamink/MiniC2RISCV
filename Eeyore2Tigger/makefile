CC = g++
LEX = flex
YACC = bison
OBJECT = tigger
HEADERS += node.h reg.h table.h lex.cc
OBJS += yacc.o node.o reg.o table.o
SOURCE += node.cc node.h reg.cc reg.h table.cc table.h yacc.y lex.l

$(OBJECT): $(OBJS)
	$(CC) -o $(OBJECT) $(OBJS) -std=c++11 -ly -ll

%.o: %.cc $(HEADERS) 
	$(CC) -c -o $@ $<

%.cc: %.y
	$(YACC) -o $@ $< --verbose

%.cc: %.l
	$(LEX) -o $@ $<

clean:
	@rm -f $(OBJECT) *.o 1600012807.tar yacc.cc lex.cc

tar: $(SOURCE)
	tar -cvf 1600012807.tar $(SOURCE) makefile