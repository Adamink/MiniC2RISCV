OBJS += parse.o env.o node.o util.o lex.o
HEADERS += parse.h util.h node.h type.h env.h
SOURCE += env.cc lex.l node.cc parse.y util.cc ${HEADERS}
TESTFOLDER += ../Test/MiniC2EeyoreTest
eeyore: $(OBJS)
	g++ -o $@ $(OBJS) -std=c++11 -ly -ll

# rules
%.cc: %.y
	bison -o $@ $< --verbose

%.cc: %.l
	flex -o $@ $<

%.o: %.cc $(HEADERS)
	g++ -c -o $@ $< -std=c++11

test0: eeyore
	./$< < ${TESTFOLDER}/01_main.c > ${TESTFOLDER}/01_main.e
	@cat ${TESTFOLDER}/01_main.e

test5: eeyore
	./$< < ${TESTFOLDER}/05_funcdefn.c > ${TESTFOLDER}/05_funcdefn.e
	@cat ${TESTFOLDER}/05_funcdefn.e

test6: eeyore
	./$< < ${TESTFOLDER}/06_add.c > ${TESTFOLDER}/06_add.e
	@cat ${TESTFOLDER}/06_add.e

test11: eeyore
	./$< < ${TESTFOLDER}/11_if_else.c > ${TESTFOLDER}/11_if_else.e
	@cat ${TESTFOLDER}/11_if_else.e

test16: eeyore
	./$< < ${TESTFOLDER}/16_equal.c > ${TESTFOLDER}/16_equal.e
	@cat ${TESTFOLDER}/16_equal.e	

test21: eeyore
	./$< < ${TESTFOLDER}/21_arr_sum.c > ${TESTFOLDER}/21_arr_sum.e
	@cat ${TESTFOLDER}/21_arr_sum.e	

tar: $(SOURCE)
	tar -cvf 1600012807.tar $(SOURCE) makefile

clean: 
	@rm -f eeyore *.o lex.cc 1600012807.tar