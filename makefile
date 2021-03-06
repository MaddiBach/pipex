NAME = pipex

FLAGS = -Wall -Werror -Wextra -g3 
LIBFT = -L libft -lft

OBJS_DIR = .obj
INCLUDES = includes
LIBFT_PATH = libft

SRCSB = \
main_bonus.c \
parsing.c \
lists.c \
utils.c \
get_next_line/get_next_line.c \
get_next_line/get_next_line_utils.c \
clean.c

SRCS = \
main.c \
parsing.c \
lists.c \
utils.c \
get_next_line/get_next_line.c \
get_next_line/get_next_line_utils.c \
clean.c

OBJB = $(SRCSB:.c=.o)

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




