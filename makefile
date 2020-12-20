# Použitý překladač
CC = gcc
CFLAGS = -Wall -Wextra -pedantic -ansi

# Binární soubory projektu
BIN = bin/railways
OBJ = main.o load_data.o graph.o point.o

# Návody pro sestavení projektu
$(BIN): $(OBJ)
	$(CC) $(OBJ) -o $(BIN) $(CFLAGS)

main.o: main.c
	gcc -c main.c $(CFLAGS)

operators.o: load_data.c load_data.h
	gcc -c load_data.c $(CFLAGS)

bin/graph.o: graph.c graph.h
	gcc -c graph.c $(CFLAGS)

bin/point.o: point.c point.h
	gcc -c point.c $(CFLAGS)

# Na Windows místo rm bude del!
clean:
	rm -f $(BIN) $(OBJ)