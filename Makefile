NAME		= miniRT
CC			= cc
CFLAGS		= -Wall -Wextra -Werror -I./includes -I./lib/libft -I./lib/get_next_line
LDFLAGS		= -lm -lmlx -lXext -lX11

SRC_MAND	= src/core/minirt.c \
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
			  src/utils/error.c

SRC_BONUS	= src/core/minirt.c \
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
			  src/utils/error.c

GNL_SRC		= lib/get_next_line/get_next_line.c \
			  lib/get_next_line/get_next_line_utils.c

OBJ_MAND	= $(SRC_MAND:.c=.o) $(GNL_SRC:.c=.o)
OBJ_BONUS	= $(SRC_BONUS:.c=.o) $(GNL_SRC:.c=.o)

MAND_MARK	= .mandatory_mark
BONUS_MARK	= .bonus_mark

.SECONDARY: $(OBJ_BONUS) $(OBJ_MAND)

all: $(MAND_MARK)

$(MAND_MARK): $(OBJ_MAND)
	rm -f $(BONUS_MARK)
	make -C lib/libft
	$(CC) $(OBJ_MAND) -Llib/libft -lft $(LDFLAGS) -o $(NAME)
	@echo "✓ miniRT compiled (mandatory)"
	@touch $(MAND_MARK)

bonus: $(BONUS_MARK)

$(BONUS_MARK): $(OBJ_BONUS)
	rm -f $(MAND_MARK)
	make -C lib/libft
	$(CC) $(OBJ_BONUS) -Llib/libft -lft $(LDFLAGS) -o $(NAME)
	@echo "✓ miniRT compiled (bonus)"
	@touch $(BONUS_MARK)

%.o: %.c
	@$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJ_MAND) $(OBJ_BONUS)
	make -C lib/libft clean
	@echo "✓ Object files cleaned"

fclean: clean
	rm -f $(NAME) $(MAND_MARK) $(BONUS_MARK)
	make -C lib/libft fclean
	@echo "✓ miniRT cleaned"

re: fclean all

.PHONY: all bonus clean fclean re