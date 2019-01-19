CC = g++
LEX = flex
YACC = bison
OBJECT = tigger
HEADERS += node.h manager.h output.h debug.h regmap.h
OBJS += yacc.o node.o manager.o regmap.o output.o debug.o

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

test1: $(OBJECT)
	./$(OBJECT) < test/01_main.ee > test/01_main.ti 

test2: $(OBJECT)
	./$(OBJECT) < test/05_funcdefn.ee > test/05_funcdefn.ti 

test3: $(OBJECT)
	./$(OBJECT) < test/24_suminput.ee > test/24_suminput.ti 

test4: $(OBJECT)	
	./$(OBJECT) < test/26_manyreg.ee > test/26_manyreg.ti