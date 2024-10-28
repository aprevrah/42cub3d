CC = cc # compiler
CFLAGS = -Wall -Werror -Wextra -g
RM = rm -f
AR = ar -rcs

NUM_PROC = $(shell nproc)
MAKEFLAGS = --jobs$(NUM_PROC)

SRCS = ft_atoi.c ft_bzero.c ft_calloc.c ft_isalnum.c ft_isalpha.c \
 ft_isascii.c ft_isdigit.c ft_isprint.c ft_itoa.c ft_memchr.c \
 ft_memcmp.c ft_memcpy.c ft_memmove.c ft_memrchr.c ft_memset.c ft_putchar_fd.c \
 ft_putendl_fd.c ft_putnbr_fd.c ft_putstr_fd.c ft_split.c ft_strchr.c ft_strdup.c \
 ft_striteri.c ft_strjoin.c ft_strlcat.c ft_strlcpy.c ft_strlen.c ft_strmapi.c \
 ft_strncmp.c ft_strnstr.c ft_strrchr.c ft_strtrim.c ft_substr.c ft_tolower.c \
 ft_toupper.c \
 \
 ft_printf.c ft_put_i.c ft_put_hex.c ft_put_p.c ft_put_u.c ft_put_s.c ft_put_c.c \
 \
 get_next_line_bonus.c get_next_line_utils_bonus.c

B_SRCS = ft_lstnew.c ft_lstadd_front.c ft_lstsize.c ft_lstlast.c ft_lstadd_back.c \
 ft_lstdelone.c ft_lstclear.c ft_lstiter.c ft_lstmap.c

OBJS = $(SRCS:.c=.o)
B_OBJS = $(B_SRCS:.c=.o)

NAME = libft.a

all: $(NAME)

bonus: $(B_OBJS)
	$(AR) $(NAME) $(B_OBJS)

%.o: %.c
	$(CC) $(CFLAGS) -c -o $@ $<

$(NAME): $(OBJS)
	$(AR) $(NAME) $(OBJS)

clean:
	$(RM) $(OBJS) $(B_OBJS)

fclean: clean
	$(RM) $(NAME)

re: fclean
	+make all

.PHONY: all clean fclean re bonus
