OBJECT = g--
DIR_E = ./MiniC2Eeyore/
DIR_T = ./Eeyore2Tigger/
DIR_R = ./Tigger2RISC-V/
DIR_EXAMPLE = ./example/
EXAMPLE += ${DIR_EXAMPLE}1.s ${DIR_EXAMPLE}2.s ${DIR_EXAMPLE}3.s ${DIR_EXAMPLE}4.s ${DIR_EXAMPLE}5.s ${DIR_EXAMPLE}6.s ${DIR_EXAMPLE}7.s ${DIR_EXAMPLE}8.s ${DIR_EXAMPLE}9.s ${DIR_EXAMPLE}10.s ${DIR_EXAMPLE}11.s ${DIR_EXAMPLE}12.s ${DIR_EXAMPLE}13.s ${DIR_EXAMPLE}14.s ${DIR_EXAMPLE}15.s ${DIR_EXAMPLE}16.s ${DIR_EXAMPLE}17.s
EXAMPLE_SRC += ${DIR_EXAMPLE}1.c ${DIR_EXAMPLE}2.c ${DIR_EXAMPLE}3.c ${DIR_EXAMPLE}4.c ${DIR_EXAMPLE}5.c ${DIR_EXAMPLE}6.c ${DIR_EXAMPLE}7.c ${DIR_EXAMPLE}8.c ${DIR_EXAMPLE}9.c ${DIR_EXAMPLE}10.c ${DIR_EXAMPLE}11.c ${DIR_EXAMPLE}12.c ${DIR_EXAMPLE}13.c ${DIR_EXAMPLE}14.c ${DIR_EXAMPLE}15.c ${DIR_EXAMPLE}16.c ${DIR_EXAMPLE}17.c

E = $(DIR_E)eeyore
T = $(DIR_T)tigger
R = $(DIR_R)riscv64

$(OBJECT): g--.cc $(E) $(T) $(R) 
	g++ -o $@ $< -std=c++11

$(E): 
	$(MAKE) -C $(DIR_E)

$(T): 
	$(MAKE) -C $(DIR_T)

$(R):
	$(MAKE) -C $(DIR_R)

tar: $(SOURCE)
	tar -cvf 吴箫_1600012807.tar *

clean: 
	@rm -rf $(OBJECT) $(E) $(T) $(R) 吴箫_1600012807.tar *.o

example: $(EXAMPLE)

$(EXAMPLE): $(OBJECT) $(EXAMPLE_SRC)
	for name in $(EXAMPLE_SRC); do \
	./$(OBJECT) $$name ; \
	done