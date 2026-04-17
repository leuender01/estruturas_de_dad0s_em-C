#=========Variaveis==========

CC= clang
FLAG= -Wall
CMD= clear
OBJ_DIR= ./objects
BIN_DIR= ./bin
COD_DIR= ./codigo-fonte
BIN= arvore
HEADER= $(COD_DIR)/arvore-de-busca-AVL.h
SOURCE= $(COD_DIR)/arvore-binaria-de-busca.c $(COD_DIR)/arvore-de-busca-AVL.c

OBJ := $(addprefix $(OBJ_DIR)/, $(notdir $(SOURCE:.c=.o)))

all: $(OBJ)
	$(CC) $(FLAG) $(OBJ) $(COD_DIR)/main.c -o $(BIN_DIR)/$(BIN)


$(OBJ_DIR)/%.o: $(COD_DIR)/%.c $(HEADER)
	@mkdir -p $(OBJ_DIR)
	$(CC) -c $< -o $@

run:
	$(BIN_DIR)/$(BIN)