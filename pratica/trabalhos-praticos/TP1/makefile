# O objetivo é a produção do executável lab
all: lab

#lab precisa do arquivo objeto lab.o
lab: lab.o
	gcc -o lab lab.o

#lab.o precisa do arquivo fonte main.c
lab.o: main.c
	gcc -o lab.o main.c -c -W -Wall

clean:
	rm -rf *.o *~ lab
