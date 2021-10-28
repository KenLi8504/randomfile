main: random.o
	gcc -o main random.o

random.o: random.c
	gcc -c random.c
