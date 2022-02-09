NAME	=	pipex

CFILES	=	cleanup.c \
			errors.c \
			execute.c \
			heredoc.c \
			init.c \
			parse.c \
			pipex.c \
			pipex_utils.c \
			redirection.c

SRC_DIR	=	src

SRCS	=	${addprefix ${SRC_DIR}/, ${CFILES}}

OBJ_DIR	=	obj

OBJS	=	${addprefix ${OBJ_DIR}/, ${CFILES:.c=.o}}

H_DIR	=	incl

CC		=	gcc

CFLAGS	=	-Wall -Wextra -Werror

AR		=	ar

ARFLAGS	=	rcs

RM		=	rm -f


${OBJ_DIR}/%.o:	${SRC_DIR}/%.c
	@mkdir -p ${OBJ_DIR}
	${CC} ${CFLAGS} -I${H_DIR} -o $@ -c $<

all:	${NAME}

libft: 
		${MAKE} bonus -C ./libft

${NAME}:	libft ${OBJS}
			${CC} ${CFLAGS} -lft -Llibft ${OBJS} -o ${NAME}

clean:	
	${RM} ${OBJS}
	${RM} -r ${OBJ_DIR}

fclean:	clean
	${RM} ${NAME}

re:	fclean all

bonus:	all

.PHONY: all clean fclean re bonus libft
