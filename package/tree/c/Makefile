CC = gcc
SRC = src/test.c $(wildcard src/*/*.c)
OBJ = $(SRC:.c=.o)
BIN = test
FLAGS = -Wall -Wextra -Werror -pedantic

%.o: %.c
	$(CC) $(FLAGS) -g -c $< -o $@

$(BIN): $(OBJ)
	$(CC) $(OBJ) -o $(BIN)

.PHONY: clean
clean:
	@rm $(OBJ)
	@rm $(BIN)
