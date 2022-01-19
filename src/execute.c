#include "../incl/pipex.h"
#include "../libft/libft.h"

int	try_exec(t_args *args, int cmd_index)
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

int	ft_exec(t_args *args, int cmd_index)
{
	pid_t	proc_id;
	pid_t	wait_id;
	int		pipe_fds[2];
	int		status;

	// to remove
	(void)cmd_index;
	// end of remove
	pipe(pipe_fds);
	proc_id = fork();
	if (proc_id == 0)
	{
		close(pipe_fds[1]);
		status = dup2(pipe_fds[0], STDIN_FILENO);
		close(pipe_fds[0]);
		if (try_exec(args, 1))
			exit(1);
	}

	close(pipe_fds[0]);
	dup2(pipe_fds[1], STDOUT_FILENO);
	wait_id = waitpid(proc_id, &status, 0);
	return (WEXITSTATUS(status));
}
