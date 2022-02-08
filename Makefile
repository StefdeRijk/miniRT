SRC = miniRT.c check_range.c parse_elements.c parse_general.c parse_number.c\
	parse_vec.c parse_check.c

NAME = miniRT
GNL_DIR = get_next_line
GNL = $(GNL_DIR)/get_next_line.a
VEC_DIR = vec
VEC = $(VEC_DIR)/vec.a
LIBFT_DIR = libft
LIBFT = $(LIBFT_DIR)/libft.a
INCLUDES = -Lmlx -lmlx -framework OpenGL -framework AppKit

ifndef DEBUG
	FLAGS = -Wall -Wextra -Werror
else
	FLAGS = -Wall -Wextra
endif

all: libft get_next_line vec $(NAME)

$(NAME): $(SRC) $(GNL) $(LIBFT) $(NAME).h
	gcc $(FLAGS) -I. $(SRC) $(LIBFT) $(VEC) $(GNL) $(INCLUDES) -o $(NAME)

libft:
	$(MAKE) bonus -C $(LIBFT_DIR)

get_next_line:
	$(MAKE) -C $(GNL_DIR)

vec:
	$(MAKE) -C $(VEC_DIR)

clean:
	$(MAKE) clean -C $(LIBFT_DIR)
	$(MAKE) clean -C $(GNL_DIR)
	$(MAKE) clean -C $(VEC_DIR)

fclean: clean
	$(MAKE) fclean -C $(LIBFT_DIR)
	$(MAKE) fclean -C $(GNL_DIR)
	$(MAKE) fclean -C $(VEC_DIR)
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re libft vec get_next_line
