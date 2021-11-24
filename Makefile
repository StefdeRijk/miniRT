SRC = miniRT.c

NAME = miniRT
MLX_DIR = minilibx_macos
MLX = $(MLX_DIR)/libmlx.a
LIBFT = libft/libft.a
LIBFT_DIR = libft
INCLUDES = -framework OpenGL -framework AppKit

ifndef DEBUG
	FLAGS = -Wall -Wextra -Werror
else
	FLAGS = -Wall -Wextra
endif

all: $(NAME)

$(NAME): $(SRC) $(LIBFT) $(MLX) $(NAME).h
	gcc $(FLAGS) -I. $(SRC) $(LIBFT) $(MLX) $(INCLUDES) -o $(NAME)

$(LIBFT):
	$(MAKE) bonus -C libft

$(MLX):
	$(MAKE) -C $(MLX_DIR)

clean:
	$(MAKE) clean -C $(LIBFT_DIR)
	$(MAKE) clean -C $(MLX_DIR)

fclean: clean
	$(MAKE) fclean -C $(LIBFT_DIR)
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re
