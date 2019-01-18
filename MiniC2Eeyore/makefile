OBJS += parse.o env.o node.o util.o lex.o
HEADERS += parse.h util.h node.h type.h env.h

%.cc: %.y
	bison -o $@ $<

%.cc: %.l
	flex -o $@ $<

%.o: %.cc $(HEADERS)
	g++ -c o $@ $<

eeyore: $(OBJS)
	g++ -o $@ $(OBJS) -std=c++11 -ly -ll
