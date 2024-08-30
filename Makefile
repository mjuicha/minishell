CC = cc

FLAGS = -Wall -Wextra -Werror

INCLUDE = minishell.h

SRC = main.c

OBJ = $(SRC:%.c=%.o)

NAME = minishell

all:	$(NAME)

$(NAME):	$(OBJ)
	$(CC) $(FLAGS) -o $(NAME) $(OBJ)

clean:
	rm -rf $(OBJ)

fclean: clean
	rm -rf $(NAME)

re: fclean all

.PHONY:	all clean fclean re