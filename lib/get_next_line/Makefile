NAME = get_next_line.a
CFILES = get_next_line.c get_next_line_utils.c
OFILES = $(CFILES:.c=.o)
CC = cc
CFLAGS = -Wall -Wextra -Werror
AR = ar rcs
RM = rm -f

all: $(NAME)

$(NAME): $(OFILES)
	$(AR) $(NAME) $(OFILES)

.c.o:
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	$(RM) $(OFILES)

fclean: clean
	$(RM) $(NAME)

re: fclean all

.PHONY: all clean fclean re