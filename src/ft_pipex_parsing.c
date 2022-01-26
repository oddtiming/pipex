#include "../incl/pipex.h"

void	args_init(t_args *args)
{
	ft_bzero((void *)args, sizeof(t_args));
}

void	pipex_parse_args(t_args *args, int argc, char const *argv[], char const *envp[])
{
	char	*path_full;
	int		i;

	//Since argv[0], argv[1], and argv[argc-1] are not commands
	args_init(args);
	args->cmds_count = argc - 3;
	//Set args->in_file
	args->in_file = ft_strdup(argv[1]);
	//Set args->pathv[] from $PATH in envp[], each path its own string in pathv[]
	if ((path_full = get_env_var(envp, "PATH")) != NULL)
	{
		args->pathv = ft_split(path_full, ':');
		ft_strcat_iter(args->pathv, "/");
		free(path_full);
	}
	
	//to remove:
	(void) argc;
	(void) argv;
	(void) envp;
	//end of remove

	//Set the cmds into their respective positions in args->cmds[]
	i = 0;
	args->cmds = malloc(sizeof(char ***));
	while (i < args->cmds_count)
	{
		args->cmds[i] = ft_split(argv[i + 2], ' ');
		//NEED TO ADD A MALLOC_CHECK HERE todo
		i++;
	}
	//NULL-terminate the array of char arrays.
	args->cmds[i] = NULL;
	//Set args->out_file
	// if (argv[argc - 1][0] != '/')
	// 	args->out_file = ft_strjoin((char const *)ft_get_last_token(get_env_var(envp, "PWD"), '/'), argv[argc - 1]);
	// else
		args->out_file = ft_strdup(argv[argc - 1]);
	args->envp_ptr = (char **)envp;
	parse_test(args);
	return ;
}