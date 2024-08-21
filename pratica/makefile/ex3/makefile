# neste terceiro exeplo, os arquivos serão organizados em pastas

# nome do projeto
PROJ_NAME=hello

# todos os arquivos "*.c"
C_SOURCE=$(wildcard ./source/*.c)

# todos os arquivos "*.h"
H_SOURCE=$(wildcard ./source/*.h)

# define o nome e local dos arquivos objetos, substituindo a pasta source pela objects e a extensão .c pela .o
OBJ=$(subst .c,.o,$(subst source,objects,$(C_SOURCE)))

# escolhe o compilador
CC=gcc

# flags para o compilador
CC_FLAGS=-c         \
         -W         \
         -Wall      \
         -ansi      \
         -pedantic

# comando utilizado como target do clean
RM = rm -rf

# agora pode ser realizada a compilação e linkagem
all: objFolder $(PROJ_NAME)

# define os pré-requisitos do arquivo final como todos seus arquivos objeto e imprime os passos realizados
$(PROJ_NAME): $(OBJ)
	@ echo 'Construindo o binário usando o linker GCC: $@'
	$(CC) $^ -o $@
	@ echo 'Binário pronto!: $@'
	@ echo ' '

#define os pré-requisitos dos arquivos objeto como o arquivo fonte -.c e o arquivo de cabeçalho -.h
./objects/%.o: ./source/%.c ./source/%.h
	@ echo 'Construindo target usando o compilador GCC: $<'
	$(CC) $< $(CC_FLAGS) -o $@
	@ echo ' '

#define os pré-requisitos de main.o como o arquivo fonte -.c e o arquivo de cabeçalho -.h
./objects/main.o: ./source/main.c $(H_SOURCE)
	@ echo 'Construindo target usando o compilador GCC: $<'
	$(CC) $< $(CC_FLAGS) -o $@
	@ echo ' '

# define a pasta de objetos
objFolder:
	@ mkdir -p objects

# comando de limpeza
clean:
	@ $(RM) ./objects/*.o $(PROJ_NAME) *~
	@ rmdir objects

# este comando existe para todos os arquivos "falsos"
.PHONY: all clean