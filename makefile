CC = gcc
CFLAGS = -Wall -Wextra -pedantic -ansi

BIN = bin/railways
OBJ = main.o load_data.o graph.o write_data.o algorithms.o

$(BIN): $(OBJ)
	$(CC) $(OBJ) -o $(BIN) $(CFLAGS)

main.o: Source\main.c
	gcc -c Source\main.c $(CFLAGS)

load_data.o: Source\load_data.c Headers\load_data.h
	gcc -c Source\load_data.c $(CFLAGS)

graph.o: Source\graph.c Headers\graph.h
	gcc -c Source\graph.c $(CFLAGS)

write_data.o: Source\write_data.c Headers\write_data.h
	gcc -c Source\write_data.c $(CFLAGS)

algorithms.o: Source\algorithms.c Headers\algorithms.h
	gcc -c Source\algorithms.c $(CFLAGS)

clean:
	rm -f $(BIN) $(OBJ)