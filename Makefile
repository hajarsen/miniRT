NAME		= miniRT
CC			= cc
CFLAGS		= -Wall -Wextra -Werror -I./includes -I./lib/libft -I./lib/get_next_line
LDFLAGS		= -lm -lmlx -lXext -lX11

SRC_MANDATORY	= src/core/minirt.c \
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

SRC_BONUS		= src/core/minirt.c \
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

GNL_SRC			= lib/get_next_line/get_next_line.c \
				  lib/get_next_line/get_next_line_utils.c

OBJ_MANDATORY	= $(SRC_MANDATORY:.c=.o) $(GNL_SRC:.c=.o)
OBJ_BONUS		= $(SRC_BONUS:.c=.o) $(GNL_SRC:.c=.o)

HEADERS			= includes/minirt.h

MANDATORY_MARK	= .mandatory_mark
BONUS_MARK		= .bonus_mark

all: $(MANDATORY_MARK)

$(MANDATORY_MARK): $(OBJ_MANDATORY)
	@rm -f $(BONUS_MARK)
	@make -C lib/libft
	@$(CC) $(OBJ_MANDATORY) -Llib/libft -lft $(LDFLAGS) -o $(NAME)
	@echo "✓ miniRT (mandatory) compiled"
	@touch $(MANDATORY_MARK)

bonus: $(BONUS_MARK)

$(BONUS_MARK): $(OBJ_BONUS)
	@rm -f $(MANDATORY_MARK)
	@make -C lib/libft
	@$(CC) $(OBJ_BONUS) -Llib/libft -lft $(LDFLAGS) -o $(NAME)
	@echo "✓ miniRT (bonus) compiled"
	@touch $(BONUS_MARK)

%.o: %.c $(HEADERS)
	@$(CC) $(CFLAGS) -c $< -o $@

clean:
	@rm -f $(OBJ_MANDATORY) $(OBJ_BONUS)
	@rm -f $(MANDATORY_MARK) $(BONUS_MARK)
	@make -C lib/libft clean
	@echo "✓ Object files cleaned"

fclean: clean
	@rm -f $(NAME)
	@make -C lib/libft fclean
	@echo "✓ miniRT cleaned"

re: fclean all

.PHONY: all bonus clean fclean re