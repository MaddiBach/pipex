NAME = pipex

FLAGS = -Wall -Werror -Wextra -g 
LIBFT = -L libft -lft

OBJS_DIR = .obj
INCLUDES = includes
LIBFT_PATH = libft

SRCS = \
main.c \
parsing.c \
lists.c \
utils.c \
get_next_line/get_next_line.c \
get_next_line/get_next_line_utils.c \
clean.c

OBJ = $(SRCS:.c=.o)

all: ${NAME}

${NAME}: ${OBJ}
	make bonus -C ./libft
	gcc ${FLAGS} ${OBJ} libft/libft.a -o ${NAME}

re: clean all
lib:
	@make -C ./libft

clean:
	@make clean -C ./libft
	@rm -f ${OBJ}




