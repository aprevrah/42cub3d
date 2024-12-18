CC = cc
CFLAGS = -Wall -Werror -Wextra
RM = rm -f

SRC_DIR = src
OBJ_DIR = objs

SRCS = $(addprefix $(SRC_DIR)/,\
main.c draw.c hooks.c oper.c \
parsing/parse_1.c parsing/parse_2.c parsing/parse_3.c parsing/parse_4.c parsing/parse_5.c parsing/parse_6.c parsing/parse_7.c \
debug/debug.c debug/debug_minimap.c debug/line.c\
init/keys.c init/player.c init/init.c\
raycast/init_ray.c raycast/raycast.c raycast/utils.c\
render.c free.c  pixel.c minimap.c mouse.c error.c)

OBJS = $(patsubst $(SRC_DIR)/%.c, $(OBJ_DIR)/%.o, $(SRCS))

NAME = cub3D

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

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c #
	@mkdir -p $(dir $@)
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

bonus: all

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
.PHONY: all clean fclean re bonus prof