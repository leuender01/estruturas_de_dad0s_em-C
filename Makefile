#=========Variaveis==========

CC= clang
FLAG= -Wall
CMD= clear
OBJ_DIR= ./objects
BIN_DIR= ./bin
COD_DIR= ./codigo-fonte
BIN= arvoreAvl
HEADER= $(COD_DIR)/arvore-de-busca-AVL.h
SOURCE= $(COD_DIR)/arvore-binaria-de-busca.c $(COD_DIR)/arvore-de-busca-AVL.c $(COD_DIR)/Queue.c
BUILD=  $(COD_DIR)/arvore-de-busca-AVL.c

OBJ := $(addprefix $(OBJ_DIR)/, $(notdir $(SOURCE:.c=.o)))

all: $(OBJ) $(BIN_DIR)/$(BIN)
	$(CC) $(FLAG) $(OBJ) $(COD_DIR)/main.c -o $(BIN_DIR)/$(BIN)
	./verificar.sh

$(BIN_DIR)/$(BIN):
	@mkdir -p $(BIN_DIR)

$(OBJ_DIR)/%.o: $(COD_DIR)/%.c $(HEADER)
	@mkdir -p $(OBJ_DIR)
	$(CC) -c $< -o $@

build: clean all run
	
clean:
	rm $(OBJ_DIR)/*.o

run:
	$(BIN_DIR)/$(BIN)
