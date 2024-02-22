CC = cc
CFLAGS = -g #-Wall -Werror -Wextra
RM = rm -f

SRC_DIR = src
OBJ_DIR = objs

SRCS = $(addprefix $(SRC_DIR)/,\
main.c draw.c matrix_utils.c parse.c render.c)

OBJS = $(patsubst $(SRC_DIR)/%.c, $(OBJ_DIR)/%.o, $(SRCS))

NAME = fdf

$(NAME): $(OBJ_DIR) $(OBJS)
	make -C ./libft all
	$(CC) $(CFLAGS) $(OBJS) -L./libft -lft -lmlx -L/lib -Imlx -lXext -lX11 -lm -o $(NAME)

all: $(OBJ_DIR) $(NAME)

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	$(CC) $(CFLAGS) -I/include -Imlx_linux -O0 -c -o $@ $<

$(OBJ_DIR):
	mkdir -p $(OBJ_DIR)

clean:
	$(RM) -r $(OBJ_DIR)
	make -C ./libft clean

fclean: clean
	$(RM) $(NAME)
	make -C ./libft fclean

re: fclean all

.PHONY: all clean fclean re
