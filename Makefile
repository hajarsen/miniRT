NAME = miniRT
CC = cc
CFLAGS = -Wall -Wextra -Werror
INCLUDES = -I./includes -I./lib/libft -I./lib/get_next_line
LDFLAGS = -lm -lmlx -lXext -lX11

CFILES_MANDATORY = src/core/minirt.c \
				   src/core/colors.c \
				   src/core/lighting.c \
				   src/core/render_rt.c \
				   src/core/render_utils.c \
				   src/core/window.c \
				   src/parsing/parser.c \
				   src/parsing/parser_utils.c \
				   src/parsing/parse_elements.c \
				   src/parsing/parse_float.c \
				   src/parsing/parse_vector.c \
				   src/parsing/parse_colors.c \
				   src/parsing/parse_objects.c \
				   src/math/math_utils.c \
				   src/math/math_utils1.c \
				   src/math/math_utils2.c \
				   src/math/math_utils3.c \
				   src/math/math_utils4.c \
				   src/render/camera.c \
				   src/render/intersections_cylinder.c \
				   src/render/intersections_cylinder_utils.c \
				   src/render/intersections_manager.c \
				   src/render/intersections_simple.c \
				   src/render/intersections_utils.c \
				   src/utils/array.c \
				   src/utils/error.c \
				   lib/get_next_line/get_next_line.c

CFILES_BONUS = src/core/minirt.c \
			   src/core/colors_bonus.c \
			   src/core/lighting.c \
			   src/core/checkerboard.c \
			   src/core/render_rt.c \
			   src/core/render_utils_bonus.c \
			   src/core/window.c \
			   src/parsing/parser.c \
			   src/parsing/parser_utils.c \
			   src/parsing/parse_elements.c \
			   src/parsing/parse_float.c \
			   src/parsing/parse_vector.c \
			   src/parsing/parse_colors.c \
			   src/parsing/parse_objects.c \
			   src/math/math_utils.c \
			   src/math/math_utils1.c \
			   src/math/math_utils2.c \
			   src/math/math_utils3.c \
			   src/math/math_utils4.c \
			   src/render/camera.c \
			   src/render/intersections_cylinder.c \
			   src/render/intersections_cylinder_utils.c \
			   src/render/intersections_manager.c \
			   src/render/intersections_simple.c \
			   src/render/intersections_utils.c \
			   src/utils/array.c \
			   src/utils/error.c \
			   lib/get_next_line/get_next_line.c

OFILES_MANDATORY = $(CFILES_MANDATORY:.c=.o)
OFILES_BONUS = $(CFILES_BONUS:.c=.o)
RM = rm -f

all: $(NAME)

$(NAME): $(OFILES_MANDATORY)
	make -C lib/libft
	make -C lib/get_next_line
	$(CC) $(OFILES_MANDATORY) -Llib/libft -lft $(LDFLAGS) -o $(NAME)

bonus: $(OFILES_BONUS)
	make -C lib/libft
	$(CC) $(OFILES_BONUS) -Llib/libft -lft $(LDFLAGS) -o $(NAME)

.c.o:
	$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

clean:
	$(RM) $(OFILES_MANDATORY) $(OFILES_BONUS)
	make -C lib/libft clean
	make -C lib/get_next_line clean

fclean: clean
	$(RM) $(NAME)
	make -C lib/libft fclean
	make -C lib/get_next_line fclean

re: fclean all

.PHONY: all bonus clean fclean re
.SECONDARY = $(OFILES_MANDATORY) $(OFILES_BONUS)