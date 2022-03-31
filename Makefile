NAME = pipex

FLAGS = -Wall -Werror -Wextra -g3 
LIBFT = -L libft -lft

OBJS_DIR = .obj
INCLUDES = includes
LIBFT_PATH = libft

SRCSB = \
main_bonus.c \
parsing_bonus.c \
lists_bonus.c \
utils_bonus.c \
get_next_line/get_next_line.c \
get_next_line/get_next_line_utils.c \
clean.c

SRCS = \
main.c \
parsing.c \
get_next_line/get_next_line.c \
get_next_line/get_next_line_utils.c \
clean.c

OBJB = $(SRCSB:.c=.o)

OBJ = $(SRCS:.c=.o)

all: ${NAME}

${NAME}: ${OBJ}
	make bonus -C ./libft
	gcc ${FLAGS} ${OBJ} libft/libft.a -o ${NAME}

bonus: ${OBJB}
	make bonus -C ./libft
	gcc ${FLAGS} ${OBJB} libft/libft.a -o ${NAME}


re: fclean all

lib:
	@make re -C ./libft

clean:
	@make clean -C ./libft
	@rm -f ${OBJ} ${OBJB}

fclean: clean
	@rm -f ${NAME}
	






