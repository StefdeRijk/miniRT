SRC = line.c vec.c vec2f.c vec2i.c vec3f.c vec3i.c vec_free.c\
	vec3f_math.c vec3f_vec_math.c vec3f_equal.c

OBJ = $(SRC:.c=.o)

NAME = vec.a

ifndef FLAGS
ifndef DEBUG
	FLAGS = -Wall -Wextra -Werror -O3
	CC = gcc
else
	FLAGS = -Wall -Wextra -fsanitize=address -g -O3
	CC = clang
endif
endif

all: $(NAME)

$(NAME): $(OBJ)
	ar rcs $@ $^

%.o: %.c
	$(CC) $(FLAGS) -c $^ -o $@ -I..

clean:
	rm -f $(OBJ)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re
