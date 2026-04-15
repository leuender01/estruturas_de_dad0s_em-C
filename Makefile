#=========Variaveis==========

CC= clang
FLAG= -Wall
CMD= clear
OBJ_DIR= ./objects
BIN_DIR= ./bin
COD_DIR= ./codigo-fonte
MAIN= main.c ## a onde vai rodar
BIN= merge_sort ## nome do binario
HEADER= merge_sort.h ## arquivo de cabeçalho
OBJ= merge_sort.o  ## arquivo objeto
COD= merge_sort.c  ## deficnir codigo fonte

#======Codigo-principal======
all: $(OBJ_DIR)/$(OBJ) bash
	$(CC) $(FLAG) $(OBJ_DIR)/$(OBJ) $(COD_DIR)/$(MAIN) -o $(BIN_DIR)/$(BIN)

$(OBJ_DIR)/$(OBJ): $(COD_DIR)/$(COD) $(COD_DIR)/$(HEADER)
	$(CC) $(FLAG) -c $(COD_DIR)/$(COD) -o $(OBJ_DIR)/$(OBJ)

clean: 
	rm $(OBJ_DIR)/*.o

build: clean all run
	
bash: 
	./verificar.sh

run:
	$(BIN_DIR)/$(BIN)