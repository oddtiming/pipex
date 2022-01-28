#include "../incl/pipex.h"


t_status	parse_args(t_main_container *container, int argc, char **argv, char *const *envp)
{
	t_status	stat_parse;

	//DO NOT MOVE THIS STEP
	container->nb_cmds = argc - 3;	//Since redirections account for args += 2, and argv[0] is the program name
	
	stat_parse = init_container(&container);
	// ERROR HANDLING

	stat_parse = init_file(container->in_file, argv[1]);
	// ERROR HANDLING
	
	stat_parse = init_file(container->out_file, argv[argc - 1]);
	// ERROR HANDLING
	
	stat_parse = parse_pathv(&(container->pathv), envp);
	// ERROR HANDLING

	stat_parse = parse_cmds(container->first_cmd, argv, container->nb_cmds);
	// ERROR HANDLING
	return (stat_parse);
}

t_status	parse_pathv(char ***pathv, char *const *envp)
{
	char		*envp_path;

	envp_path = get_env_var(envp, "PATH");
	if (!envp_path)
		return (E_ENVPATH);
	*pathv = ft_split(envp_path, ':');
	if (!*pathv)
		return (E_SPLIT);
	ft_strcat_iter(*pathv, "/");
	if (!*pathv)
		return (E_SPLIT);
	free(envp_path);
	return (0);
}

t_status	parse_cmds(t_cmd *first_cmd, char **argv, size_t nb_cmds)
{
	t_cmd	*cmd_i;
	size_t	i;
	int		*pipe_fds;

	//We need n - 1 pipes, since both ends of the3 pipe chain have I/O redirection 
	pipe_fds = malloc(2 * (nb_cmds - 1) * sizeof(int));
	i = 0;
	//Could easily be condensed
	while (i < (nb_cmds - 1))
	{
		if ( pipe( pipe_fds + (2*i) ) );
			return(E_PIPE);
		i++;
	}
	i = 0;
	while (i < nb_cmds)
	{
		cmd_i = first_cmd + i;
		cmd_i->cmd_index = i;
		cmd_i->cmd_argv = ft_split(argv[2 + i], ' ');
		if (!(cmd_i->cmd_argv[0]))
			return (E_SPLIT);
		if (i > 0)
			cmd_i->in_fd = *(pipe_fds + i + 1);
		if (i < nb_cmds - 1)
			cmd_i->out_fd = *(pipe_fds + i + 1);
	}
	free (pipe_fds);
	return (0);
}