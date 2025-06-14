NAME	= libft.a
HNAME	= libft.h
FLAGS	= -Wall -Wextra -Werror -I.
RM		= rm -f

SRC = ./ft_atoi.c \
	./ft_bzero.c \
	./ft_calloc.c \
	./ft_isalnum.c \
	./ft_isalpha.c \
	./ft_isascii.c \
	./ft_isdigit.c \
	./ft_isprint.c \
	./is_space.c \
	./ft_itoa.c \
	./ft_lstadd_back.c \
	./ft_lstadd_front.c \
	./ft_lstclear.c \
	./ft_lstdelone.c \
	./ft_lstiter.c \
	./ft_lstlast.c \
	./ft_lstnew.c \
	./ft_lstsize.c \
	./ft_memchr.c \
	./ft_memcmp.c \
	./ft_memcpy.c \
	./ft_memmove.c \
	./ft_memset.c \
	./ft_printf/ft_aux.c \
	./ft_printf/ft_percent.c \
	./ft_printf/ft_printf.c \
	./ft_printf/ft_putchar.c \
	./ft_printf/ft_putdecimal.c \
	./ft_printf/ft_puthexamai.c \
	./ft_printf/ft_puthexamin.c \
	./ft_printf/ft_putptr.c \
	./ft_printf/ft_putstr.c \
	./ft_printf/ft_putunsign.c \
	./ft_putchar_fd.c \
	./ft_putendl_fd.c \
	./ft_putnbr_fd.c \
	./ft_putstr_fd.c \
	./ft_split.c \
	./ft_strchr.c \
	./ft_strdup.c \
	./ft_striteri.c \
	./ft_strjoin.c \
	./ft_strlcat.c \
	./ft_strlcpy.c \
	./ft_strlen.c \
	./ft_strmapi.c \
	./ft_strcmp.c \
	./ft_strncmp.c \
	./ft_strnstr.c \
	./ft_strrchr.c \
	./ft_strtrim.c \
	./ft_substr.c \
	./ft_tolower.c \
	./ft_toupper.c \
	./get_next_line/get_next_line_utils_bonus.c \
	./get_next_line/get_next_line_bonus.c \
	./what_is.c \

OBJ		= $(SRC:.c=.o)

all: $(NAME)

$(NAME): $(OBJ)
	ar -rcs $(NAME) $(OBJ)

%.o: %.c
	$(CC) -c $(FLAGS) $< -o $@

clean:
	rm -f $(OBJ)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re
#.SILENT: