NAME = pipex

FLAGS = -Wall -Werror -Wextra -g
LIBFT = -L libft -lft

OBJS_DIR = .obj
INCLUDES = includes
LIBFT_PATH = libft

SRCS = \
main.c \
parsing.c \
lists.c

OBJ = $(SRCS:.c=.o)

all: ${NAME}

${NAME}: ${OBJ}
	make -C ./libft
	gcc ${FLAGS} ${OBJ} libft/libft.a -o ${NAME}


lib:
	@make -C ./libft

clean:
	@make clean -C ./libft
	@rm -f ${OBJ}




