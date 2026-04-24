#=========Variaveis==========

CC= clang
FLAG= -Wall
CMD= clear
OBJ_DIR= ./objects
BIN_DIR= ./bin
COD_DIR= ./codigo-fonte
HEADER= 
BIN= 
SOURCE= 

ARVORE_AVL_COD= $(COD_DIR)/arvore-binaria-de-busca.c $(COD_DIR)/arvore-de-busca-AVL.c $(COD_DIR)/Queue.c
ARVORE_AVL_OBJ := $(addprefix $(OBJ_DIR)/, $(notdir $(ARVORE_AVL_COD:.c=.o)))
ARVORE_AVL_HEADER := $(addprefix $(COD_DIR)/, $(notdir $(ARVORE_AVL_COD:.c=.h))) $(COD_DIR)/arvore-base.h


arvore_avl: $(ARVORE_AVL_OBJ) $(BIN_DIR)/arvoreAvl
	$(CC) $(FLAG) $(ARVORE_AVL_OBJ) $(COD_DIR)/teste_avl.c -o $(BIN_DIR)/arvoreAvl
	./verificar.sh
	./$(BIN_DIR)/arvoreAvl

$(BIN_DIR)/$(BIN):
	@mkdir -p $(BIN_DIR)

$(BIN_DIR)/arvoreAvl:
	@mkdir -p $(BIN_DIR)

$(ARVORE_AVL_OBJ): $(ARVORE_AVL_COD) $(ARVORE_AVL_HEADER)
	@mkdir -p $(OBJ_DIR)
	$(CC) -c $(COD_DIR)/arvore-binaria-de-busca.c -o  $(OBJ_DIR)/arvore-binaria-de-busca.o
	$(CC) -c $(COD_DIR)/arvore-de-busca-AVL.c -o  $(OBJ_DIR)/arvore-de-busca-AVL.o
	$(CC) -c $(COD_DIR)/Queue.c -o  $(OBJ_DIR)/Queue.o

build: clean all run
	
clean:
	rm $(OBJ_DIR)/*.o

run:
	$(BIN_DIR)/$(BIN)
