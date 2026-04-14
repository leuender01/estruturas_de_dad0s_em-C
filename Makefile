#=========Variaveis==========

CC= clang
FLAG= -Wall
CMD= clear
OBJ_DIR= ./objects
BIN_DIR= ./bin
COD_DIR= ./codigo-fonte
HEADER= data.h ## arquivo de cabeçalho
OBJ= enums.o  ## arquivo objeto
COD= enums.c  ## deficnir codigo fonte

#======Codigo-principal======
enum: $(OBJ_DIR)/$(OBJ) bash
	$(CC) $(FLAG) $(OBJ_DIR)/$(OBJ) $(COD_DIR)/main.c -o $(BIN_DIR)/program

$(OBJ_DIR)/$(OBJ): $(COD_DIR)/$(COD) $(COD_DIR)/$(HEADER)
	$(CC) $(FLAG) -c $(COD_DIR)/$(COD) -o $(OBJ_DIR)/$(OBJ)

clean: 
	rm $(OBJ_DIR)/*.o

bash: 
	./verificar.sh