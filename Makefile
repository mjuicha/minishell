CC = cc
CFLAGS = -Wall -Wextra -Werror

SRC_DIR = .
OBJ_DIR = obj
INCLUDE_DIR = includes
LIBFT_DIR = libft

SRC = main.c handle_signals.c ft_parser.c ft_lexer.c main_utils.c ft_init_env.c ft_init_shell.c \
ft_tokenizer.c ft_reset.c syntax_error.c ft_expand.c ft_heredoc.c ft_fd_manager.c
OBJ = $(SRC:%.c=%.o)

INCLUDE = -I $(INCLUDE_DIR) -I/Users/${USER}/.brew/opt/readline/include
LIBS = -L$(LIBFT_DIR) -L/Users/${USER}/.brew/opt/readline/lib -lft -lreadline -lncurses

NAME = minishell

all: $(LIBFT_DIR)/libft.a $(NAME)

$(NAME): $(OBJ) $(LIBFT_DIR)/libft.a
	$(CC) $(CFLAGS) -o $(NAME) $(OBJ) $(LIBS)

$(LIBFT_DIR)/libft.a:
	$(MAKE) -C $(LIBFT_DIR)

%.o: %.c
	@mkdir -p $(OBJ_DIR)
	$(CC) $(CFLAGS) $(INCLUDE) -c $< -o $@

clean:
	rm -rf $(OBJ)
	$(MAKE) -C $(LIBFT_DIR) clean

fclean: clean
	rm -rf $(NAME)
	$(MAKE) -C $(LIBFT_DIR) fclean

re: fclean all

.PHONY: all clean fclean re
