##
## EPITECH PROJECT, 2025
## myword
## File description:
## makefile
##

MAIN = src/main.c

SRC =	src/create_window.c	\
		src/dispatch.c	\
		src/free.c	\
		src/event.c	\
		src/math/create_coor.c	\
		src/math/random_height.c	\
		src/textbox/event.c	\
		src/textbox/text_box.c	\
		src/draw_map/handle_draw.c	\
		src/draw_map/event.c	\
		src/initiate.c			\
		src/buttons/create_button.c	\
		src/buttons/draw_button.c	\
		src/buttons/init_buttons.c	\
		src/buttons/destroy_buttons.c	\
		src/math/find_tile.c			\
		src/save/save.c	\
		src/menu/event.c	\
		src/menu/menu.c	\
		src/save/show_save.c	\
		src/save/event.c	\
		src/save/get_save.c		\
		src/buttons/is_it_on_button.c		\
		src/buttons/plus_button.c			\
		src/buttons/minus_button.c			\
		src/buttons/reload_button.c			\

OBJ = $(SRC:.c=.o) $(MAIN:.c=.o)

NAME = my_world

CFLAGS = -Wall -Wextra -g3

CPPFLAGS = -iquoteinclude -iquotelib

CSFMLFLAG = -lcsfml-system -lcsfml-window -lcsfml-graphics -lcsfml-audio

LDLIB = -Llib -lmy -lm

all:	$(NAME)

$(NAME):	$(OBJ)
	$(MAKE) -C ./lib
	$(CC) -o $(NAME) $(OBJ) $(CSFMLFLAG) $(LDLIB)

clean:
	$(MAKE) -C ./lib clean
	$(RM) $(OBJ)

fclean:	clean
	$(MAKE) -C ./lib fclean
	$(RM) $(NAME)

re:	fclean all

.PHONY: all clean fclean re
