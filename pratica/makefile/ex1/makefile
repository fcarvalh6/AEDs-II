# makefile simples

# makefiles contém instruções para a compilação de arquivos. Essas receitas são compostas de "targets", pré-requisitos e receitas

#indo de cima pra baixo, a versão final do código que queremos é o executável hello. O comando "make all" irá compilar até chegar no target all, resultando no executável hello
all: hello

#o executável "hello" possui por sua vez dois requisitos, os arquivos de objeto de main.c e helloworld.c. A linha abaixo tabulada é a receita, o comando que o makefile deve executar
hello: main.o helloworld.o 
	gcc -o hello main.o helloworld.o 

#a compilação de main.c para main.o precisa por sua vez do arquivo header helloworld.h, já que ele contém o cabeçalho da função helloWorld
main.o: main.c helloworld.h
	gcc -o main.o main.c -c -W -Wall -ansi -pedantic

#note que opções estão sendo passadas para o gcc, precedidas pelo sinal de menos
helloworld.o: helloworld.c helloworld.h
	gcc -o helloworld.o helloworld.c -c -W -Wall -ansi -pedantic

#esta opção de limpeza será apenas acionada com make clean e irá apagar todos os arquivos produzidos durante a compilação
clean:
	rm -rf *.o *~ hello