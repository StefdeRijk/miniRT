SRC = line.c vec.c vec2f.c vec2i.c vec3f.c vec3i.c vec_free.c\
	vec3f_math.c vec3f_vec_math.c

OBJ = $(SRC:.c=.o)

NAME = vec.a

ifndef DEBUG
	FLAGS = -Wall -Wextra -Werror
else
	FLAGS = -Wall -Wextra
endif

all: $(NAME)

$(NAME): $(OBJ)
	ar rcs $@ $^

%.o: %.c
	gcc $(FLAGS) -c $^ -o $@ -I..

clean:
	rm -f $(OBJ)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re
