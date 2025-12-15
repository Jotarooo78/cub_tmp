NAME = cub3D
CC = cc
CFLAGS = -Wall -Wextra -Werror -g3
LDFLAGS = -L./src/utils/libx -L./src/utils/libft
LDLIBS = -lmlx -lft -lm -lXext -lX11
RM = rm -f

SRCS = \
	src/main.c \
	src/parsing/parse_text_color.c \
	src/parsing/parse_map.c \
	src/parsing/utils.c \
	src/parsing/utils2.c \
	src/parsing/error.c \
	src/parsing/check.c \
	src/parsing/check2.c \
	src/parsing/split_with_delimiter.c \
	src/parsing/parse_map2.c \
	src/utils/init.c \
	src/utils/destructors.c \
	src/exec/raycasting.c \
	src/exec/raycasting_utils.c \
	src/exec/render.c \
	src/exec/render_utils.c \
	src/exec/texture.c \
	src/exec/texture_init.c \
	src/exec/player_move.c \
	src/exec/player_rotate.c \
	src/exec/player_init.c \
	src/exec/input_handler.c \
	src/exec/exit.c \

OBJ_DIR = obj
DEP_DIR = $(OBJ_DIR)
OBJS = $(SRCS:src/%.c=$(OBJ_DIR)/%.o)
DEPS = $(OBJS:.o=.d)

LIBFT = src/utils/libft/libft.a
LIBX = src/utils/libx/libmlx.a

all: $(NAME)

$(NAME): $(OBJS) $(LIBFT) $(LIBX)
	$(CC) $(CFLAGS) $(OBJS) $(LDFLAGS) $(LDLIBS) -o $(NAME)

$(LIBFT):
	make -C src/utils/libft

$(LIBX):
	make -C src/utils/libx

$(OBJ_DIR)/%.o: src/%.c
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) -I./src/utils/libft -I./src/utils/libx -I./includes -c $< -o $@

-include $(DEPS)

clean:
	$(RM) -r $(OBJ_DIR)

fclean: clean
	$(RM) $(NAME)
	make fclean -C src/utils/libft
	-make clean -C src/utils/libx

re: fclean all

.PHONY: all clean fclean re
