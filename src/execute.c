#include "../incl/pipex.h"
#include "../libft/libft.h"

int	try_exec(t_args *args)
{
	int		i;
	char	*curr_path;

	i = 0;
	while (args->pathv[i])
	{
		curr_path = ft_strjoin(args->pathv[i], args->cmd1[0]);
		execve(curr_path, args->cmd1, args->envp_ptr);
		i++;
	}
	return (-1);
}

int	ft_exec_cmd1(t_args *args)
{
	pid_t	proc_id;
	pid_t	wait_id;
	int		pipe_fds[2];
	int		status;

	pipe(pipe_fds);
	proc_id = fork();
	if (proc_id == 0)
	{
		close(pipe_fds[1]);
		status = dup2(pipe_fds[0], STDIN_FILENO);
		close(pipe_fds[0])
		if (try_exec(args))
			exit(1);
	}

	close(pipe_fds[0]);
	dup2(STDOUT_FILENO, pipe_fds[1]);
	wait_id = waitid(proc_id, &status, 0);
	return (WEXITSTATUS(status));
}