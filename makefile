# Použitý překladač
CC = gcc
CFLAGS = -Wall -Wextra -pedantic -ansi

# Binární soubory projektu
BIN = bin/railways
OBJ = main.o load_data.o graph.o point.o write_data.o algorithms.o

# Návody pro sestavení projektu
$(BIN): $(OBJ)
	$(CC) $(OBJ) -o $(BIN) $(CFLAGS)

main.o: Source\main.c
	gcc -c Source\main.c $(CFLAGS)

load_data.o: Source\load_data.c Headers\load_data.h
	gcc -c Source\load_data.c $(CFLAGS)

graph.o: Source\graph.c Headers\graph.h
	gcc -c Source\graph.c $(CFLAGS)

point.o: Source\point.c Headers\point.h
	gcc -c Source\point.c $(CFLAGS)

write_data.o: Source\write_data.c Headers\write_data.h
	gcc -c Source\write_data.c $(CFLAGS)

algorithms.o: Source\algorithms.c Headers\algorithms.h
	gcc -c Source\algorithms.c $(CFLAGS)

# Na Windows místo rm bude del!
clean:
	rm -f $(BIN) $(OBJ)