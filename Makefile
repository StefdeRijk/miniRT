SRC = miniRT.c

NAME = miniRT
MLX_DIR = minilibx_macos
MLX = $(MLX_DIR)/libmlx.a
GNL_SRC = get_next_line/get_next_line.c get_next_line/get_next_line_utils.c
GNL = $(GNL_SRX:.c=.o)
LIBFT = libft/libft.a
LIBFT_DIR = libft
INCLUDES = -framework OpenGL -framework AppKit

ifndef DEBUG
	FLAGS = -Wall -Wextra -Werror
else
	FLAGS = -Wall -Wextra
endif

all: $(NAME)

$(NAME): $(SRC) $(GNL) $(LIBFT) $(MLX) $(NAME).h
	gcc $(FLAGS) -I. $(SRC) $(GNL) $(LIBFT) $(MLX) $(INCLUDES) -o $(NAME) 

$(LIBFT):
	$(MAKE) bonus -C libft

$(MLX):
	$(MAKE) -C $(MLX_DIR)

$(GNL): $(GNL_SRC) get_next_line/get_next_line.h
	gcc $(FLAGS) $(GNL_SRC) -o $(GNL) 

clean:
	$(MAKE) clean -C $(LIBFT_DIR)
	$(MAKE) clean -C $(MLX_DIR)

fclean: clean
	$(MAKE) fclean -C $(LIBFT_DIR)
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re
