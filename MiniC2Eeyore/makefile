OBJECT = eeyore
OBJS += parse.o env.o node.o util.o lex.o
HEADERS += parse.h util.h node.h type.h env.h
SOURCE += env.cc lex.l node.cc parse.y util.cc ${HEADERS}

$(OBJECT): $(OBJS)
	g++ -o $@ $(OBJS) -std=c++11 -ly -ll

# rules
%.cc: %.y
	bison -o $@ $< --verbose

%.cc: %.l
	flex -o $@ $<

%.o: %.cc $(HEADERS)
	g++ -c -o $@ $< -std=c++11
	
tar: $(SOURCE)
	tar -cvf 1600012807.tar $(SOURCE) makefile

clean: 
	@rm -f $(OBJECT) *.o lex.cc 1600012807.tar