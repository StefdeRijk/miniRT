SRC_MANDATORY = ft_atoi.c ft_isprint.c ft_putchar_fd.c ft_striteri.c\
	ft_strnstr.c ft_bzero.c ft_itoa.c ft_putendl_fd.c ft_strjoin.c\
	ft_strrchr.c ft_calloc.c ft_memchr.c ft_putnbr_fd.c ft_strlcat.c\
	ft_strtrim.c ft_isalnum.c ft_memcmp.c ft_putstr_fd.c ft_strlcpy.c\
	ft_substr.c ft_isalpha.c ft_memcpy.c ft_split.c ft_strlen.c ft_tolower.c\
	ft_isascii.c ft_memmove.c ft_strchr.c ft_strmapi.c ft_toupper.c\
	ft_isdigit.c ft_memset.c ft_strdup.c ft_strncmp.c \
	\
	ft_putmem_fd.c ft_isspace.c ft_realloc.c ft_memdup.c ft_lstremove.c\
	ft_lstremove_n.c ft_swap.c ft_max.c ft_lstremove_back.c ft_swapf.c ft_min.c\
	ft_atoi_base.c ft_abs.c ft_strcmp.c ft_print_bits.c ft_modf.c ft_sign.c\
	ft_atoi_skip.c
SRC_BONUS = ft_lstadd_back_bonus.c ft_lstdelone_bonus.c ft_lstmap_bonus.c\
			ft_lstadd_front_bonus.c ft_lstiter_bonus.c ft_lstnew_bonus.c\
		 	ft_lstclear_bonus.c ft_lstlast_bonus.c ft_lstsize_bonus.c
ifdef DO_BONUS
	SRC = $(SRC_MANDATORY) $(SRC_BONUS)
else
	SRC = $(SRC_MANDATORY)
endif

OBJ = $(SRC:.c=.o)
OBJ_BONUS = $(SRC_BONUS:.c=.o)

NAME = libft.a

ifndef DEBUG
	FLAGS = -Wall -Wextra -Werror -O3
	CC = gcc
else
	FLAGS = -Wall -Wextra -fsanitize=address -g -O3
	CC = clang
endif

all: $(NAME)

$(NAME): $(OBJ)
	ar rcs $@ $^

%.o: %.c
	$(CC) $(FLAGS) -c $^ -o $@

clean:
	rm -f $(OBJ) $(OBJ_BONUS)

fclean: clean
	rm -f $(NAME)

re: fclean all

bonus:
	$(MAKE) DO_BONUS=1

.PHONY: all clean fclean re bonus
