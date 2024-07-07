EXEC = #name
FLAGS = -Wall -Wextra -Werror
PATH_SRC = ./srcs/
SRC = #.c files
OBJ = $(SRC:.c=.o)
CC = gcc

all: $(EXEC)

$(EXEC): $(OBJ)
	$(CC) $(FLAGS) $(OBJ) -o $(EXEC)

%.o: %.c
	$(CC) $(FLAGS) -c $< -o $@

clean:
	/bin/rm -f $(OBJ)

fclean: clean
	/bin/rm -f $(EXEC)

.PHONY: all clean fclean
