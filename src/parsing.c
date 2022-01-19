#include "../incl/pipex.h"
#include "../libft/libft.h"

void	parse_test(t_args *args)
{
	char	*buff;

	buff = malloc(2);
	buff[1] = 0;
	if (args->cmds_count)
		printf("args->cmds_count = %d\n", args->cmds_count);
	else
		printf("args->cmds_count has not yet been initialized\n");
	if (args->in_file)
		printf("args->in_file = %s\n", args->in_file);
	else
		printf("args->in_file has not yet been initialized\n");
	if (args->out_file)
		printf("args->out_file = %s\n", args->out_file);
	else
		printf("args->out_file has not yet been initialized\n");
	if (args->pathv)
		ft_print_split(args->pathv, "pathv");
	else
		printf("args->pathv has not yet been initialized\n");
	if (args->envp_ptr)
		ft_print_split(args->envp_ptr, "envp_ptr");
	else
		printf("args->envp_ptr has not yet been initialized\n");
	if (args->cmds)
	{
		for (int i = 0; i < args->cmds_count; i++)
		{
			buff[0] = i + '0';
			ft_print_split(args->cmds[i], buff);
		}
	}
	else
		printf("args->cmds has not yet been initialized\n");
	free(buff);
}

void	args_init(t_args *args)
{
	*args = *(t_args *)malloc(sizeof(t_args));
	ft_bzero((void *)args, sizeof(t_args));
}

void	parse_args(t_args *args, int argc, char const *argv[], char const *envp[])
{
	char	*path_full;
	int		i;
	
	i = 0;
	printf("in parse_args, ARG_NUMBERS = %d and argc = %d\n", NARGS, argc);
	if (argc < (NARGS))
	{
		write(2, "pipex: wrong # of args, pal.\n", ft_strlen("pipex: wrong # of args, pal.\n"));
		exit(2);
	}
	//Since argv[0], argv[1], and argv[argc-1] are not commands
	args->cmds_count = argc - 3;
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
	args->cmds = malloc(sizeof(char ***));
	while (i < args->cmds_count)
	{
		args->cmds[i] = ft_split(argv[i + 2], ' ');
		//NEED TO ADD A MALLOC_CHECK HERE
		i++;
	}
	//NULL-terminate the array of char arrays.
	args->cmds[i] = NULL;
	// args->cmd1 = ft_split(argv[2], ' ');
	// args->cmd2 = ft_split(argv[3], ' ');
	args->out_file = ft_strdup(argv[argc - 1]);
	args->envp_ptr = (char **)envp;
	parse_test(args);
	return ;
}