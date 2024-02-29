CC = cc
CFLAGS = -Wall -Werror -Wextra
RM = rm -f

SRC_DIR = src
OBJ_DIR = objs

SRCS = $(addprefix $(SRC_DIR)/,\
main.c draw.c hooks.c init.c matrix_affine.c oper.c parse.c render.c utils.c)

OBJS = $(patsubst $(SRC_DIR)/%.c, $(OBJ_DIR)/%.o, $(SRCS))

NAME = fdf

$(NAME): $(OBJ_DIR) $(OBJS)
	make -C ./libft all
	$(CC) $(CFLAGS) $(OBJS) -L./libft -lft -lmlx -L/lib -Imlx -lXext -lX11 -lm -o $(NAME)

all: $(OBJ_DIR) $(NAME)

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	$(CC) $(CFLAGS) -I/include -Imlx_linux -c -o $@ $<
#Debugflag -O0

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
