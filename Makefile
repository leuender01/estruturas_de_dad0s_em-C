#=========Variaveis==========

CC= clang
FLAG= -Wall
CMD= clear

#======Compila=Principal=====

enum: enums.o

	$(CC) $(FLAG) enums.o main.c -o enum

#====Cria_As_Dependencias=====
enum.o: data.h

	$(CC) $(FLAG) -c enums.c

#===Remove=Arquivos=Objetos===

clean:
	rm -rf *.o

#===========COMODISMO==========

build: clean enum run

#===========Executa============

run:
	$(CMD)
	./enum