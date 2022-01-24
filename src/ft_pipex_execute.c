#include "../incl/pipex.h"

static int	execute_cmd_n(t_args *args, int cmd_index)
{
	int		i;
	char	*curr_path;
	int		pipe_fds[2];

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

void	pipex_execute_cmds(t_args *args, int write_end)
{
	static int	cmd_index;
	int			pipe_fds[2];
	int			status;
	pid_t		pid_child;

	if (cmd_index < (args->cmds_count - 1));
	{
		pipe(pipe_fds);
		//write the file-redirected stream
	}
	pid_child = fork();
	dup2(write_end, pipe_fds[1]);
	if (child_pid == 0)
		//following function needs the pipe fds
		//Needs to redirect stdout onto a write end of a pipe
		execute_cmd_n(args, cmd_index);
	close(pipe_fds[1]);
	close(pipe_fds[0]);
	waitpid(pid_child, &status, E)
	if (cmd_index == args->cmds_count - 1)
	{
		return ;
	}
	cmd_index+=1;

}
