NAME	=	pipex

SHELL	=	bash

GREEN	=	"\033[0;32m"
GREEN_LITERAL	=	\033[0;32m
BLUE	=	"\033[0;34m"
BLUE_LITERAL	=	\033[0;34m
RED	=	"\033[0;31m"
RED_LITERAL	=	\033[0;31m
RESET_COL	=	"\033[0m" 
RESET_LITERAL	=	\033[0m

CFILES	=	cleanup.c \
			errors.c \
			execute.c \
			heredoc.c \
			init.c \
			parse.c \
			pipex.c \
			redirect.c \
			utils.c

SRC_DIR	=	src

SRCS	=	$(addprefix $(SRC_DIR)/, $(CFILES))

OBJ_DIR	=	obj

OBJS	=	$(addprefix $(OBJ_DIR)/, $(CFILES:.c=.o))

INC	=	incl

CC		=	gcc

CFLAGS	=	-Wall -Wextra -Werror

AR		=	ar

ARFLAGS	=	rcs

RM_OBJS		=	rm -rf $(OBJ_DIR)
RM_OBJS_OUT	=	$$($(RM_OBJS) 2>&1 | sed -e 's/error/\\\033[0;31merror\\\033[0m/g' -e 's/warning/\\\033[0;33mwarning\\\033[0m/g')
RM_PROG		=	rm -f $(NAME)
RM_PROG_OUT	=	$$($(RM_PROG) 2>&1 | sed -e 's/error/\\\033[0;31merror\\\033[0m/g' -e 's/warning/\\\033[0;33mwarning\\\033[0m/g')

COMPILE_PIPEX	=	$(CC) $(CFLAGS) -lft -Llibft $(OBJS) -o $(NAME)
COMPILE_PIPEX_OUT	=	$$($(COMPILE_PIPEX) 2>&1 | sed -e 's/error/\\\033[0;31merror\\\033[0m/g' -e 's/warning/\\\033[0;33mwarning\\\033[0m/g')

COMPILE_C	=	$(CC) $(CFLAGS) -I$(INC) -o $@ -c $<
COMPILE_C_OUT	=	$$($(COMPILE_C) 2>&1 | sed -e 's/error/\\\033[0;31merror\\\033[0m/g' -e 's/warning/\\\033[0;33mwarning\\\033[0m/g')

$(OBJ_DIR)/%.o:	$(SRC_DIR)/%.c
	@mkdir -p $(OBJ_DIR)
	@echo -e "$(BLUE_LITERAL) $^\t--> $@ $(RESET_LITERAL)$(COMPILE_C_OUT)"	


# @echo -e "$(COMPILE_PIPEX_OUT)"

all:	$(NAME)

silent_libft:
	@echo -e "-------------------libft.a-------------------"
	@echo -e $(BLUE)"\n>>>>>>>> Compiling libft.a ..."$(RESET_COL)
	@make -s bonus -C ./libft
	@echo -e $(GREEN)">>>>>>>> Archive successful\n>>>>>>>>\n"$(RESET_COL)

$(NAME):	libft $(OBJS)
	@echo -e "\n-------------------$(NAME)-------------------"
	@echo -e "$(BLUE_LITERAL)\n>>>>>>>> Compiling $(NAME) ...$(RESET_LITERAL)$(COMPILE_PIPEX_OUT)"
	@echo -e $(GREEN)">>>>>>>> Build successful\n>>>>>>>>"$(RESET_COL)

clean:	
	@echo -e "$(BLUE_LITERAL)\n>>>>>>>> Deleting obj files$(RESET_LITERAL)$(RM_OBJS_OUT)"
	@echo -e "$(RED_LITERAL)>>>>>>>> obj files deleted\n>>>>>>>>$(RESET_LITERAL)"

fclean:	clean
	@echo -e "$(BLUE_LITERAL)\n>>>>>>>> Deleting $(NAME)$(RESET_LITERAL)$(RM_PROG_OUT)"
	@echo -e "$(RED_LITERAL)>>>>>>>> $(NAME) deleted\n>>>>>>>>$(RESET_LITERAL)"

libft: silent_libft

re:	fclean all

bonus:	all

.PHONY: all clean fclean re bonus libft
