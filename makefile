OBJECT = g--
DIR_E = ./MiniC2Eeyore/
DIR_T = ./Eeyore2Tigger/
DIR_R = ./Tigger2RISC-V/

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
	tar -cvf 1600012807.tar $(E) $(T) $(R) makefile

clean: 
	@rm -f $(OBJECT) $(E) $(T) $(R)