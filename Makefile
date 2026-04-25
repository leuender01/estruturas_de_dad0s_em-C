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
ARVORE_AVL_BIN= $(BIN_DIR)/arvoreAvl
ARVORE_AVL_OBJ := $(addprefix $(OBJ_DIR)/, $(notdir $(ARVORE_AVL_COD:.c=.o)))
ARVORE_AVL_HEADER := $(addprefix $(COD_DIR)/, $(notdir $(ARVORE_AVL_COD:.c=.h))) $(COD_DIR)/arvore-base.h

MERGE_SORT_COD= $(COD_DIR)/merge_sort.c
MERGE_SORT_BIN= $(BIN_DIR)/merge_sort
MERGE_SORT_HEADER = $(COD_DIR)/merge_sort.h
MERGE_SORT_OBJ := $(addprefix $(OBJ_DIR)/, $(notdir $(MERGE_SORT_COD:.c=.o)))

merge_sort: $(MERGE_SORT_OBJ) $(MERGE_SORT_BIN)
	$(CC) $(FLAG)  $(MERGE_SORT_OBJ) $(COD_DIR)/teste_merge.c -o $(MERGE_SORT_BIN)
	./verificar.sh
	./$(MERGE_SORT_BIN)

$(MERGE_SORT_BIN):
	@mkdir -p $(BIN_DIR)

$(MERGE_SORT_OBJ): $(MERGE_SORT_HEADER)
	@mkdir -p $(OBJ_DIR)
	$(CC) -c $(MERGE_SORT_COD) -o $(MERGE_SORT_OBJ)


arvore_avl: $(ARVORE_AVL_OBJ) $(ARVORE_AVL_BIN)
	$(CC) $(FLAG) -g $(ARVORE_AVL_OBJ) $(COD_DIR)/teste_avl.c -o $(ARVORE_AVL_BIN)
	./verificar.sh
	./$(ARVORE_AVL_BIN)

$(BIN_DIR)/$(BIN):
	@mkdir -p $(BIN_DIR)

$(ARVORE_AVL_BIN):
	@mkdir -p $(BIN_DIR)

$(ARVORE_AVL_OBJ): $(ARVORE_AVL_COD) $(ARVORE_AVL_HEADER)
	$(CC) -c $(COD_DIR)/arvore-binaria-de-busca.c -o  $(OBJ_DIR)/arvore-binaria-de-busca.o
	$(CC) -c $(COD_DIR)/arvore-de-busca-AVL.c -o  $(OBJ_DIR)/arvore-de-busca-AVL.o
	$(CC) -c $(COD_DIR)/Queue.c -o  $(OBJ_DIR)/Queue.o

build: clean all run

clean:
	rm $(OBJ_DIR)/*.o

run:
	$(BIN_DIR)/$(BIN)
