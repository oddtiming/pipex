NAME	=	pipex

SHELL	=	bash

GREEN		=	\033[0;32m
BLUE		=	\033[0;34m
RED			=	\033[0;31m
RESET_COL	=	\033[0m

CFILES	=	cleanup.c \
			errors.c \
			execute.c \
			heredoc.c \
			init.c \
			parse.c \
			pipex.c \
			redirect.c \
			utils.c \
			waitpid.c

SRC_DIR	= src
SRCS	= $(addprefix $(SRC_DIR)/, $(CFILES))

OBJ_DIR	= obj
OBJS	= $(addprefix $(OBJ_DIR)/, $(CFILES:.c=.o))

INC	= incl

CC		= gcc
CFLAGS	= -Wall -Wextra -Werror -g

LIBFT_DIR	= ./libft
LIBFT		= $(LIBFT_DIR)/libft.a
LIBFT_FLAGS	= -lft -Llibft

RM_OBJS			=	rm -rf $(OBJ_DIR)
RM_OBJS_OUT		=	$$($(RM_OBJS) 2>&1 | sed -e 's/error/\\\033[0;31merror\\\033[0m/g' -e 's/warning/\\\033[0;33mwarning\\\033[0m/g')
RM_PROG			=	rm -f $(NAME)
RM_PROG_OUT		=	$$($(RM_PROG) 2>&1 | sed -e 's/error/\\\033[0;31merror\\\033[0m/g' -e 's/warning/\\\033[0;33mwarning\\\033[0m/g')
RM_LIBFT		=	make clean -sC ./libft
RM_LIBFT_OUT	=	$$($(RM_LIBFT) 2>&1 | sed -e 's/error/\\\033[0;31merror\\\033[0m/g' -e 's/warning/\\\033[0;33mwarning\\\033[0m/g')

COMPILE_PIPEX		=	$(CC) $(CFLAGS) $(LIBFT_FLAGS) $(OBJS) -o $(NAME)
COMPILE_PIPEX_OUT	=	$$($(COMPILE_PIPEX) 2>&1 | sed -e 's/error/\\\033[0;31merror\\\033[0m/g' -e 's/warning/\\\033[0;33mwarning\\\033[0m/g')

COMPILE_C		=	$(CC) $(CFLAGS) -I$(INC) -o $@ -c $<
COMPILE_C_OUT	=	$$($(COMPILE_C) 2>&1 | sed -e 's/error/\\\033[0;31merror\\\033[0m/g' -e 's/warning/\\\033[0;33mwarning\\\033[0m/g')

$(OBJ_DIR)/%.o:	$(SRC_DIR)/%.c
	@mkdir -p $(OBJ_DIR)
	@echo -e "$(BLUE)>\t$^\t--> $@ $(RESET_COL)$(COMPILE_C_OUT)"	

all: $(NAME)
	@if [ -e $(NAME) ]; \
		then \
		echo -e "$(GREEN)>>>>>>>> Compilation successful\n>>>>>>>>$(RESET_COL)"; \
	else \
		echo -e "$(RED)>>>>>>>> Compilation failed\n>>>>>>>>$(RESET_COL)"; \
	fi


$(NAME):	libft pretty_print $(OBJS)
	@echo -e "\n$(BLUE)>>>>>>>> Compiling $(NAME) ...$(RESET_COL)$(COMPILE_PIPEX_OUT)"

silent_libft:
	@echo -e "------------------ libft.a ------------------\n"
	@echo -e "$(BLUE)>>>>>>>> Archiving libft.a ...$(RESET_COL)"
	@make -s bonus -C $(LIBFT_DIR)
	@if [ -e $(LIBFT) ]; \
		then \
		echo -e "$(GREEN)>>>>>>>> Archive successful\n>>>>>>>>$(RESET_COL)"; \
	else \
		echo -e "$(RED)>>>>>>>> Archive failed\n>>>>>>>>$(RESET_COL)"; \
	fi

libft: silent_libft

pretty_print: 
	@echo -e "\n------------------- $(NAME) -------------------"

clean:	
	@echo -e "$(RED)>>>>>>>> Deleting obj files$(RESET_COL)$(RM_OBJS_OUT)"
	@echo -e "$(GREEN)>>>>>>>> obj files deleted\n>>>>>>>>$(RESET_COL)"

clean_libft:	
	@echo -e "$(RED)>>>>>>>> make fclean -sC libft $(RESET_COL)$(RM_LIBFT_OUT)"
	@echo -e "$(GREEN)>>>>>>>> libft cleaned\n>>>>>>>>$(RESET_COL)"

fclean:	clean clean_libft
	@echo -e "$(RED)>>>>>>>> Deleting $(NAME)$(RESET_COL)$(RM_PROG_OUT)"
	@echo -e "$(GREEN)>>>>>>>> ./$(NAME) deleted\n>>>>>>>>$(RESET_COL)"

re:	fclean all

bonus:	all

.PHONY: all clean clean_libft fclean re bonus libft silent_libft pretty_print
