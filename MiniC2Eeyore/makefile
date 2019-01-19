OBJS += parse.o env.o node.o util.o lex.o
HEADERS += parse.h util.h node.h type.h env.h
TESTFOLDER += ../Test/MiniC2EeyoreTest
eeyore: $(OBJS)
	g++ -o $@ $(OBJS) -std=c++11 -ly -ll

# rules
%.cc: %.y
	bison -o $@ $< --verbose

%.cc: %.l
	flex -o $@ $<

%.o: %.cc $(HEADERS)
	g++ -c -o $@ $<

test0: eeyore
	./$< < ${TESTFOLDER}/01_main.c > ${TESTFOLDER}/01_main.e
	@cat ${TESTFOLDER}/01_main.e

test6: eeyore
	./$< < ${TESTFOLDER}/06_add.c > ${TESTFOLDER}/06_add.e
	@cat ${TESTFOLDER}/06_add.e

test11: eeyore
	./$< < ${TESTFOLDER}/11_if_else.c > ${TESTFOLDER}/11_if_else.e
	@cat ${TESTFOLDER}/11_if_else.e

test16:eeyore
	./$< < ${TESTFOLDER}/16_equal.c > ${TESTFOLDER}/16_equal.e
	@cat ${TESTFOLDER}/16_equal.e	
	
clear: 
	rm eeyore *.o parse.cc lex.cc