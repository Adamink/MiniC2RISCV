OBJECT = riscv64
OBJS += yacc.o node.o
HEADERS += node.h lex.cc
SOURCE += lex.l node.cc node.h yacc.y
BINDEPENDANCY += ../MiniC2Eeyore/eeyore ../Eeyore2Tigger/tigger

$(OBJECT): $(OBJS)
	g++ -o $@ $(OBJS) -std=c++11 -ly -ll
	
# rules
%.cc: %.y lex.cc
	bison -o $@ $< --verbose

%.cc: %.l
	flex -o $@ $<

%.o: %.cc $(HEADERS)
	g++ -c -o $@ $< -std=c++11

tar: $(SOURCE)
	tar -cvf 1600012807.tar $(SOURCE) makefile

clean:
	@rm -f $(OBJECT) *.o 1600012807.tar yacc.cc lex.cc