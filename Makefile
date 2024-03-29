CC = gcc
CFLAGS = -Wall -Wextra -pedantic -ansi -g -lm

BIN = graph.exe
OBJ = main.o load_data.o graph.o write_data.o algorithms.o

$(BIN): $(OBJ)
	$(CC) $(OBJ) -o $(BIN) $(CFLAGS)

main.o: main.c
	gcc -c main.c $(CFLAGS)

load_data.o: load_data.c load_data.h
	gcc -c load_data.c $(CFLAGS)

graph.o: graph.c graph.h
	gcc -c graph.c $(CFLAGS)

write_data.o: write_data.c write_data.h
	gcc -c write_data.c $(CFLAGS)

algorithms.o: algorithms.c algorithms.h
	gcc -c algorithms.c $(CFLAGS)

