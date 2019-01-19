OBJS += parse.o env.o node.o util.o lex.o
HEADERS += parse.h util.h node.h type.h env.h

eeyore: $(OBJS)
	g++ -o $@ $(OBJS) -std=c++11 -ly -ll

# rules
%.cc: %.y
	bison -o $@ $< --verbose

%.cc: %.l
	flex -o $@ $<

%.o: %.cc $(HEADERS)
	g++ -c -o $@ $<

clear: 
	rm *.o