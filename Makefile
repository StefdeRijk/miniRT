MLX_DIR = mlx
MLX = $(MLX_DIR)/libmlx.a
GNL_DIR = get_next_line
GNL = $(GNL_DIR)/get_next_line.a
VEC_DIR = vec
VEC = $(VEC_DIR)/vec.a
LIBFT_DIR = libft
LIBFT = $(LIBFT_DIR)/libft.a
INCLUDES = -Lmlx -lmlx -framework OpenGL -framework AppKit
SRC_BASE = check_range.c parse_elements.c parse_general.c parse_number.c\
	  parse_vec.c parse_check.c init_mlx.c color.c ray.c sphere.c\
	  parse_objects.c spot_light.c plane.c error.c get_scene.c cylinder.c\
	  parse_check_floats.c parse_element_type.c mlx_utils.c


ifndef DEBUG
	FLAGS = -Wall -Wextra -Werror -O3
else
	FLAGS = -Wall -Wextra -fsanitize=address -g -O3
endif

ifndef TEST
	NAME = miniRT
	SRC = $(SRC_BASE) miniRT.c
else
	NAME = tester
	SRC = $(SRC_BASE) unit_tests.c
endif

all: libft get_next_line vec $(NAME)

$(NAME): $(SRC) $(GNL) $(LIBFT) $(MLX) miniRT.h
	gcc $(FLAGS) -I. $(SRC) $(LIBFT) $(VEC) $(GNL) $(INCLUDES) -o $(NAME)

libft:
	$(MAKE) bonus -C $(LIBFT_DIR)

get_next_line:
	$(MAKE) -C $(GNL_DIR)

vec:
	$(MAKE) -C $(VEC_DIR)

$(MLX):
	$(MAKE) -C $(MLX_DIR)

clean:
	$(MAKE) clean -C $(LIBFT_DIR)
	$(MAKE) clean -C $(GNL_DIR)
	$(MAKE) clean -C $(VEC_DIR)
	$(MAKE) clean -C $(MLX_DIR)

fclean: clean
	$(MAKE) fclean -C $(LIBFT_DIR)
	$(MAKE) fclean -C $(GNL_DIR)
	$(MAKE) fclean -C $(VEC_DIR)
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re libft vec get_next_line
