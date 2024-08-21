# este segundo exemplo de makefile inclui algumas automações, fazendo com que ela funcione para qualquer número de arquivos com qualquer nome

# nome do projeto (nome do arquivo executável final)
PROJ_NAME=hello

# este comando armazena todos arquivos *.c por meio da função wildcard
C_SOURCE=$(wildcard *.c) 

# este comando armazena todos arquivos *.h por meio da função wildcard
H_SOURCE=$(wildcard *.h)

# os arquivos objeto são definidos, a extensão de arquivo é mudada de .c para .o
OBJ=$(C_SOURCE: .c=.o)

# o compilador gcc é escolhido
CC=gcc

# as flags para o compilador são definidas
CC_FLAGS=-c -W -Wall -ansi -pedantic

# agora pode ser realizada a compilação e linkagem
all: $(PROJ_NAME)

# hello: helloworld.o main.o \ COMPLETAR
$(PROJ_NAME): $(OBJ)
	$(CC) -o $@ $^

#
%.o: %.c %.h
	$(CC) -o $@ $< $(CC_FLAGS)

#
main.o: main.c $(H_SOURCE)
	$(CC) -o $@ $< $(CC_FLAGS)

#
clean:
	rm -rf *.o $(PROJ_NAME) *~