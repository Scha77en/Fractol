CC = cc  

SRC = main.c fractals.c hooks.c proper_exit.c

NAME = fractol

FLAGS = -Wall -Wextra -Werror -I /usr/local/include -L /usr/local/lib -lmlx -framework OpenGL -framework AppKit

RM = rm -rf

all : ${NAME}

${NAME} : ${SRC} fractol.h
	${CC} ${FLAGS} ${SRC} -o ${NAME}

clean :
	@echo All Cleaned!

fclean :
	${RM} ${NAME}

re : fclean all

.PHONY : all fclean re