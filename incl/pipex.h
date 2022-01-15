#ifndef PIPEX_H
# define PIPEX_H

# include <stdlib.h>
# include <unistd.h>
# include <errno.h>
# include <fcntl.h>

//TO REMOVE
# include <stdio.h>

# define NARGS 5

typedef struct s_args
{
	int		argc;
	char	*in_file;
	char	*out_file;
	char	**cmd1;
	char	**cmd2;
	char	**pathv;
	char	**envp_ptr;
}	t_args;

//UTILS
//Ultimately to be moved to libft submodule
char	*get_env_var(char const *envp[], char *var_name);
void	ft_print_split(char **split_arr, char *name);
void	ft_strcat_iter(char **vector, char *to_cat);

//INIT FUNCTIONS
void	args_init(t_args *args);
void	parse_args(t_args *args, int argc, char const **argv, char const **envp);

//TEST FUNCTIONS
void	access_test(t_args *args);

#endif