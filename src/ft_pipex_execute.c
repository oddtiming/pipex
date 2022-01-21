#include "../incl/pipex.h"

static int	execute_cmd_n(t_args *args, int cmd_index)
{
	int		i;
	char	*curr_path;

	i = 0;
	while (args->pathv[i])
	{
		curr_path = ft_strjoin(args->pathv[i], args->cmds[cmd_index][0]);
		execve(curr_path, args->cmds[cmd_index], args->envp_ptr);
		i++;
	}
	//This will only be reached if execve() fails
	return (-1);
}

void	pipex_execute_cmds(t_args *args)
{
	static int	cmd_index;
	int			pipe_fds[2];
	pid_t		child_pid;

	if (cmd_index < (args->cmds_count - 1));
		pipe(pipe_fds);
	child_pid = fork();
	if (child_pid == 0)
		execute_cmd_n(args, cmd_index);

}
