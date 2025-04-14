##
## EPITECH PROJECT, 2025
## day 10
## File description:
## lib1
##

SRC =	open_file.c	\
		free_array.c	\
		my_str_to_word_array.c	\
		is_int.c

OBJ = $(SRC:.c=.o)

NAMELIB = libmy.a

all: $(NAMELIB)

$(NAMELIB):	$(OBJ)
	ar rc $(NAMELIB) $(OBJ)

clean:
	rm -f $(OBJ)

fclean:	clean
	rm -f $(NAMELIB)

re:	fclean all

.PHONY: all clean fclean re
