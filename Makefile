CC = cc
CFLAGS = -Wall -Werror -Wextra -Wno-unused-function -g
RM = rm -f

SRC_DIR = src
OBJ_DIR = objs

SRCS = $(addprefix $(SRC_DIR)/,\
main.c draw.c hooks.c init.c oper.c parse.c render.c utils.c raycast.c free.c debug.c line.c pixel.c minimap.c)

OBJS = $(patsubst $(SRC_DIR)/%.c, $(OBJ_DIR)/%.o, $(SRCS))

NAME = cub3d

NUM_PROC = $(shell nproc)
MAKEFLAGS = -j$(NUM_PROC)

# Set colors
GREEN=\033[0;32m
CYAN=\033[0;36m
NC=\033[0m # No Color

$(NAME): $(OBJ_DIR) $(OBJS)
	+make -C ./libft all
	$(CC) $(CFLAGS) $(OBJS) -L./libft -lft -lmlx -L/lib -Imlx -lXext -lX11 -lm -o $(NAME)

all: $(OBJ_DIR) $(NAME)

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	$(CC) $(CFLAGS) -I/include -Imlx_linux -c -o $@ $<
#Debugflag -O0

$(OBJ_DIR):
	mkdir -p $(OBJ_DIR)

clean:
	$(RM) -r $(OBJ_DIR)
	+make -C ./libft clean

fclean: clean
	$(RM) $(NAME)
	+make -C ./libft fclean

re: fclean
	+make all

# Map to be use for profiling
MAP_PATH = assets/map.cub

# Get the current Git commit hash
COMMIT_HASH := $(shell git rev-parse --short HEAD)

# Get the current date and time
DATE_TIME := $(shell date +"%Y-%m-%d_%H-%M-%S")

# Define the directory for storing profiling data
PROFILE_DIR = "profiling/${DATE_TIME}_${COMMIT_HASH}"

prof: fclean
	$(MAKE) CFLAGS="$(CFLAGS) -pg" all
	mkdir -p "$(PROFILE_DIR)"
	./$(NAME) "$(MAP_PATH)"
	mv gmon.out $(PROFILE_DIR)/gmon.out
	cp $(NAME) "$(PROFILE_DIR)/$(NAME)"
	gprof -p -b $(PROFILE_DIR)/$(NAME) $(PROFILE_DIR)/gmon.out
	@echo "${GREEN}For more stats, use this command:${NC}"
	@echo "${CYAN}gprof $(PROFILE_DIR)/$(NAME) $(PROFILE_DIR)/gmon.out${NC}"
.PHONY: all clean fclean re prof