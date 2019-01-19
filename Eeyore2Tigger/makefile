OBJECT = tigger
HEADERS += node.h reg.h table.h lex.cc
OBJS += yacc.o node.o reg.o table.o
SOURCE += node.cc node.h reg.cc reg.h table.cc table.h yacc.y lex.l
BIN += ../MiniC2Eeyore/eeyore

$(OBJECT): $(OBJS)
	g++ -o $(OBJECT) $(OBJS) -std=c++11 -ly -ll

%.cc: %.y
	bison -o $@ $< --verbose

%.cc: %.l
	flex -o $@ $<

%.o: %.cc $(HEADERS) 
	g++ -c -o $@ $< -std=c++11

tar: $(SOURCE) $(BIN)
	tar -cvf 1600012807.tar $(SOURCE) $(BIN) makefile

clean:
	@rm -f $(OBJECT) *.o 1600012807.tar yacc.cc lex.cc
