NAME = miniRT
CC = gcc
CFLAGS = -Wall -Wextra -Werror -I./includes -I./lib/libft -I./lib/get_next_line -g
LDFLAGS = -lm -lmlx -lXext -lX11

SRC = src/core/minirt.c \
      src/core/render_rt.c \
      src/core/window.c \
      src/parsing/parser.c \
      src/parsing/parser_utils.c \
      src/parsing/parse_elements.c \
      src/parsing/parse_error.c \
      src/parsing/parse_float.c \
      src/parsing/parse_vector.c \
      src/parsing/parse_colors.c \
      src/parsing/parse_ambient.c \
      src/parsing/parse_light.c \
      src/parsing/parse_sphere.c \
      src/parsing/parse_plane.c \
      src/parsing/parse_cylinder.c \
      src/math/math_utils.c \
      src/math/math_utils1.c \
      src/math/math_utils2.c \
      src/math/math_utils3.c \
      src/render/render.c \
      src/render/camera.c \
      src/render/intersections.c \
      src/utils/array.c

GNL_SRC = lib/get_next_line/get_next_line.c \
          lib/get_next_line/get_next_line_utils.c

OBJ = $(SRC:.c=.o) $(GNL_SRC:.c=.o)

all: $(NAME)

$(NAME): $(OBJ)
	make -C lib/libft
	$(CC) $(OBJ) -Llib/libft -lft $(LDFLAGS) -o $(NAME)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJ)
	make -C lib/libft clean

fclean: clean
	rm -f $(NAME)
	make -C lib/libft fclean

re: fclean all

.PHONY: all clean fclean re