CC = gcc
CFLAGS =

SRC_DIR = .
OBJ_DIR = obj
INCLUDE_DIR = includes
LIBFT_DIR = libft

# List all source files
SRC = main.c handle_signals.c libft/ft_putstr_fd.c libft/ft_putchar_fd.c libft/ft_putendl_fd.c libft/ft_strlen.c
OBJ = $(SRC:%.c=%.o)

# Include and library paths
INCLUDE = -I $(INCLUDE_DIR) -I/Users/${USER}/.brew/opt/readline/include
LIBS = -L$(LIBFT_DIR) -L/Users/${USER}/.brew/opt/readline/lib -lft -lreadline -lncurses

NAME = minishell

# Default target
all: $(LIBFT_DIR)/libft.a $(NAME)

# Link the final executable
$(NAME): $(OBJ) $(LIBFT_DIR)/libft.a
	$(CC) $(CFLAGS) -o $(NAME) $(OBJ) $(LIBS)

# Build libft
$(LIBFT_DIR)/libft.a:
	$(MAKE) -C $(LIBFT_DIR)

# Compile source files into object files
%.o: %.c
	@mkdir -p $(OBJ_DIR)
	$(CC) $(CFLAGS) $(INCLUDE) -c $< -o $@

# Clean object files and libft
clean:
	rm -rf $(OBJ_DIR)
	$(MAKE) -C $(LIBFT_DIR) clean

# Clean everything including the executable and libft
fclean: clean
	rm -rf $(NAME)
	$(MAKE) -C $(LIBFT_DIR) fclean

# Rebuild everything
re: fclean all

.PHONY: all clean fclean re
