NAME = client server
NAME_BONUS = client_bonus server_bonus
FLAGS = -Wall -Wextra -Werror
PATH_SRC = ./srcs/

SRC_1 = $(PATH_SRC)client.c
SRC_2 = $(PATH_SRC)server.c
SRC_BONUS_1 = $(PATH_SRC)client_bonus.c
SRC_BONUS_2 = $(PATH_SRC)server_bonus.c

OBJ_1 = $(SRC_1:.c=.o)
OBJ_2 = $(SRC_2:.c=.o)
OBJ_BONUS_1 = $(SRC_BONUS_1:.c=.o)
OBJ_BONUS_2 = $(SRC_BONUS_2:.c=.o)

CC = gcc

all: $(NAME)

bonus: $(NAME_BONUS)

client: $(OBJ_1)
	$(CC) $(FLAGS) $(OBJ_1) -o client

server: $(OBJ_2)
	$(CC) $(FLAGS) $(OBJ_2) -o server

client_bonus: $(OBJ_BONUS_1)
	$(CC) $(FLAGS) $(OBJ_BONUS_1) -o client_bonus

server_bonus: $(OBJ_BONUS_2)
	$(CC) $(FLAGS) $(OBJ_BONUS_2) -o server_bonus

%.o: %.c
	$(CC) $(FLAGS) -c $< -o $@

clean:
	/bin/rm -f $(OBJ_1) $(OBJ_2) $(OBJ_BONUS_1) $(OBJ_BONUS_2)

fclean: clean
	/bin/rm -f $(NAME) $(NAME_BONUS)

re: fclean all

.PHONY: all clean fclean
