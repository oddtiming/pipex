#ifndef PIPEX_H
# define PIPEX_H

# include "../libft/libft.h"
# include <stdlib.h>
# include <unistd.h>
# include <errno.h>
# include <fcntl.h>
# include <sys/wait.h>
//TO REMOVE
# include <stdio.h>
//END OF REMOVE

# define ARGC_MIN 5

//TYPEDEFS
typedef uint_fast8_t	t_status;
//NOT SURE: I'm uncertain as to whether a uint8_t would be better

//STRUCTS
typedef struct s_file
{
	char		*filepath;
	t_status	status;
}	t_file;

typedef struct s_cmd
{
	char *const	*envp;
	char		**argv;
	t_file		cmd_file;
	int			in_fd;
	int			out_fd;
	size_t		cmd_index;
}	t_cmd;

typedef struct s_main_container
{
	t_file	*in_file;
	t_file	*out_file;
	char	**pathv;
	//Should commands be stored as a single pointer or a 2D array?
	//pointer	-->		 more risky
	//array		-->	more leak-prone
	t_cmd	*cmd1;
	size_t	cmds_count;
}	t_main_container;

// TO REMOVE
typedef struct s_args
{
	char	*in_file;
	char	*out_file;
	char	**pathv;
	char	**envp_ptr;
	char	***cmds;
	int		cmds_count;
}	t_args;
// END OF REMOVE

//UTILS
//Ultimately to be moved to libft submodule
char	*get_env_var(char const *envp[], char *var_name);
void	ft_print_split(char **split_arr, char *name);
void	ft_strcat_iter(char **vector, char *to_cat);
char	*ft_get_last_token(char *string, char delimiter);
char	*ft_strjoin_n(size_t nb_strings, ...);

//CLEANUP

//PARSING

//REDIRECTIONS

//EXECUTION

//TEST FUNCTIONS -- TO REMOVE
void	access_test(t_args *args);
void	parse_test(t_args *args);
//END OF REMOVE

#endif