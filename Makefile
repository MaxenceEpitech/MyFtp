##
## EPITECH PROJECT, 2018
## cpp
## File description:
## cpp
##

NAME		=	server

CC		=	gcc

CFLAGS		+=	-I ./include -g3 #-Wall -Wextra -Werror

RM		=	rm -f

SRCS		=	src/server.c			\
			src/tool.c			\
			src/init.c			\
			src/dir.c			\
			src/command.c			\
			src/run.c			\
			src/login.c			\
			src/new_socket.c		\
			src/get_next_line.c		\
			src/my_str_to_wordtab.c

OBJS		=	$(SRCS:.c=.o)

all:		$(NAME)

$(NAME):	$(OBJS)
		$(CC) -o $(NAME) $(OBJS)

clean:
		$(RM) $(OBJS)

fclean:		clean
		$(RM) $(NAME)

re:		fclean all

.PHONY:		all clean fclean re
