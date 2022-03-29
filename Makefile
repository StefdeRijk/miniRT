export
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
	  parse_check_floats.c parse_element_type.c mlx_utils.c math_utils.c\
	  cylinder_utils.c color_utils.c check_hits.c paraboloid.c \
	  read_bmp.c checkerboard.c checkerboard_utils.c get_texture.c paint_img.c\
	  parse_texture.c mirror.c texture.c get_angle.c object_color.c object_normal.c

ifndef DEBUG
	FLAGS = -Wall -Wextra -Werror -O3
	CC = gcc
else
	FLAGS = -Wall -Wextra -fsanitize=address -g -O3
	CC = clang
endif

ifdef PROFILE
	FLAGS := $(FLAGS) -fprofile-instr-generate -fcoverage-mapping -DPROFILE=1
	CC = clang
endif

ifndef TEST
	NAME = miniRT
	SRC = $(SRC_BASE) miniRT.c
else
	NAME = tester
	SRC = $(SRC_BASE) unit_tests.c
endif

ifdef BONUS
	FLAGS := $(FLAGS) -DBONUS=1
endif

all: libft get_next_line vec $(NAME)

$(NAME): $(SRC) $(GNL) $(LIBFT) $(MLX) miniRT.h
	$(CC) $(FLAGS) -I. $(SRC) $(LIBFT) $(VEC) $(GNL) $(INCLUDES) -o $(NAME)

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

miniclean:

minifclean: miniclean
	rm -f $(NAME)

re: fclean all

minire: minifclean all
.PHONY: all clean fclean re libft vec get_next_line minire miniclean minifclean
