all: sort

sort: ./objects/main.o ./objects/sort.o
	gcc ./objects/main.o ./objects/sort.o -o sort

./objects/main.o: ./source/main.c
	gcc -c ./source/main.c -o ./objects/main.o

./objects/sort.o: ./source/sort.c
	gcc -c ./source/sort.c -o ./objects/sort.o

clean:
	rm -rf ./objects/*.o ./sort
