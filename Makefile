NAME	=	pipex

CFILES	=	pipex.c \
			parsing.c \
			pipex_utils.c

SRC_DIR	=	src

SRCS	=	${addprefix ${SRC_DIR}/, ${CFILES}}
#OBJS	=	${SRCS:.c=.o}

OBJ_DIR	=	obj

OBJS	=	${addprefix ${OBJ_DIR}/, ${CFILES:.c=.o}}

H_DIR	=	incl

CC		=	gcc

CFLAGS	=	-Wall -Wextra -Werror

AR		=	ar

ARFLAGS	=	rcs

RM		=	rm -f

#.c.o:
#	${CC} ${CFLAGS} -c $< -o ${<:.c=.o}

${OBJ_DIR}/%.o: ${SRC_DIR}/%.c ${H_DIR}/pipex.h
	@mkdir -p ${OBJ_DIR}
	${CC} ${CFLAGS} -I${H_DIR} -o $@ -c $<

all:	${NAME}

libft: 
		${MAKE} bonus -C ./libft

#NOTE : cd is relative in Makefile and will return to main root folder 

${NAME}:	libft ${OBJS}

clean:	
	${RM} ${OBJS}
	${RM} -r ${OBJ_DIR}

fclean:	clean
	${RM} ${NAME}

re:	fclean all

bonus:	all

.PHONY: all clean fclean re bonus libft

#to add:
#Directories for srcs and for .o