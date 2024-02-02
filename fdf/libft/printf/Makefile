CC = cc # compiler
CFLAGS = -Wall -Werror -Wextra
RM = rm -f
AR = ar -rcs

SRCS = ft_printf.c ft_put_i.c ft_put_hex.c ft_put_p.c ft_put_u.c ft_put_s.c ft_put_c.c

OBJS = $(SRCS:.c=.o)

NAME = libftprintf.a

all: $(NAME)

%.o: %.c
	$(CC) $(CFLAGS) -c -o $@ $<

$(NAME): $(OBJS)
	$(AR) $(NAME) $(OBJS)

clean:
	$(RM) $(OBJS)

fclean: clean
	$(RM) $(NAME)

re: fclean all

.PHONY: all clean fclean re