#ifndef PIPEX_H
# define PIPEX_H

# include <stdlib.h>
# include <unistd.h>
# include <errno.h>
# include <fcntl.h>

//TO REMOVE
# include <stdio.h>

# define ARGS_NUMBER 4

typedef struct s_args
{
	int		argc;
	char	*in_file;
	char	*out_file;
	char	**cmd1;
	char	**cmd2;
	char	**pathv;
}	t_args;

//UTILS
//Ultimately to be moved to libft submodule
char	*get_env_var(char const *envp[], char *var_name);
void	ft_print_split(char **split_arr, char *name);

//INIT FUNCTIONS
void	args_init(t_args *args);
void	parse_args(t_args *args, int argc, char const *argv[], char const *envp[]);

#endif