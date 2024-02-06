CC = cc
CFLAGS = -g #-Wall -Werror -Wextra
RM = rm -f

SRC_DIR = src
OBJ_DIR = objs

SRCS = $(addprefix $(SRC_DIR)/,\
main.c )

B_SRCS = $(addprefix $(SRC_DIR)/,\
)

OBJS = $(patsubst $(SRC_DIR)/%.c, $(OBJ_DIR)/%.o, $(SRCS))
B_OBJS = $(patsubst $(SRC_DIR)/%.c, $(OBJ_DIR)/%.o, $(B_SRCS))

NAME = fdf
B_NAME = fdf_bonus

$(NAME): $(OBJ_DIR) $(OBJS)
	make -C ./libft all
	$(CC) $(OBJS) -L./libft -lft -lmlx -L/lib -Imlx -lXext -lX11 -lm -o $(NAME)

$(B_NAME): $(OBJ_DIR) $(B_OBJS)
	make -C ./libft all
	$(CC) $(B_OBJS) -L./libft -lft -o $(B_NAME)

all: $(OBJ_DIR) $(NAME) $(B_NAME)

bonus: $(B_NAME)

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	$(CC) $(CFLAGS) -I/include -Imlx_linux -O3 -c -o $@ $<

$(OBJ_DIR):
	mkdir -p $(OBJ_DIR)

clean:
	$(RM) -r $(OBJ_DIR)
	make -C ./libft clean

fclean: clean
	$(RM) $(NAME) $(B_NAME)
	make -C ./libft fclean

re: fclean all

.PHONY: all clean fclean re bonus
