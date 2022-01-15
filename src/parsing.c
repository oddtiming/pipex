#include "../incl/pipex.h"
#include "../libft/libft.h"

void	args_init(t_args *args)
{
	args = malloc(sizeof(t_args));
	ft_bzero(args, sizeof(t_args));
}

void	parse_args(t_args *args, int argc, char const *argv[], char const *envp[])
{
	char	*path_full;
	
	printf("in parse_args, ARG_NUMBERS = %d and argc = %d\n", NARGS, argc);
	if (argc != (NARGS) )
	{
		write(2, "pipex: wrong # of args, pal.\n", ft_strlen("pipex: wrong # of args, pal.\n"));
		exit(2);
	}
	args->in_file = ft_strdup(argv[1]);
	if ((path_full = get_env_var(envp, "PATH")) != NULL)
	{
		args->pathv = ft_split(path_full, ':');
		ft_strcat_iter(args->pathv, "/");
	}
	//to remove:
	(void) argc;
	(void) argv;
	(void) envp;
	ft_print_split(args->pathv, "pathv");
	//end of remove
	args->cmd1 = ft_split(argv[2], ' ');
	args->cmd2 = ft_split(argv[3], ' ');
	args->out_file = ft_strdup(argv[4]);
	args->envp_ptr = (char *)envp;
	return ;
}