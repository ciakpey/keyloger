main: main.o liste.o
	gcc main.o liste.o -o main

main.o: main.c
	gcc -c main.c main.h

liste.o: liste.c
	gcc -c liste.c liste.h
