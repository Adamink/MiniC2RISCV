OBJS += parse.o env.o node.o util.o lex.o
HEADERS += parse.h util.h node.h type.h env.h

%.cc: %.y
	bison -o $@ $<

%.cc: %.l
	flex -o $@ $<

eeyore: $(OBJS)
	g++ -o $@ $(OBJS) -std=c++11 -ly -ll

parse.o: parse.cc $(HEADERS)
	g++ -c -o $@ $<

lex.o: lex.cc $(HEADERS)
	g++ -c -o $@ $<

env.o: env.cc $(HEADERS)
	g++ -c -o $@ $<

node.o: node.cc $(HEADERS)
	g++ -c -o $@ $<

util.o: util.cc $(HEADERS)
	g++ -c -o $@ $<
