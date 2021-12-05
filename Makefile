SRC = miniRT.c check_range.c parse_elements.c parse_general.c parse_number.c\
	parse_vec.c

NAME = miniRT
MLX_DIR = minilibx_macos
MLX = $(MLX_DIR)/libmlx.a
GNL_DIR = get_next_line
GNL = $(GNL_DIR)/get_next_line.a
LIBFT_DIR = libft
LIBFT = $(LIBFT_DIR)/libft.a
FT_PRINTF_DIR = ft_printf
FT_PRINTF = $(FT_PRINTF_DIR)/libftprintf.a
INCLUDES = -framework OpenGL -framework AppKit

ifndef DEBUG
	FLAGS = -Wall -Wextra -Werror
else
	FLAGS = -Wall -Wextra
endif

all: libft ft_printf get_next_line $(NAME)

$(NAME): $(SRC) $(GNL) $(FT_PRINTF) $(LIBFT) $(MLX) $(NAME).h
	gcc $(FLAGS) -I. $(SRC) $(GNL) $(FT_PRINTF) $(MLX) $(INCLUDES) -o $(NAME) 

libft:
	$(MAKE) bonus -C $(LIBFT_DIR)

ft_printf:
	$(MAKE) bonus -C $(FT_PRINTF_DIR)

get_next_line:
	$(MAKE) bonus -C $(GNL_DIR)

$(MLX):
	$(MAKE) -C $(MLX_DIR)

clean:
	$(MAKE) clean -C $(LIBFT_DIR)
	$(MAKE) clean -C $(FT_PRINTF_DIR)
	$(MAKE) clean -C $(MLX_DIR)

fclean: clean
	$(MAKE) fclean -C $(LIBFT_DIR)
	$(MAKE) fclean -C $(FT_PRINTF_DIR)
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re libft ft_printf
