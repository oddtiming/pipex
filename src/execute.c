#include "../incl/pipex.h"

static void	execute_child(char *const *envp, t_cmd *cmd_i)
{
	int		status;
	
	status = 0;
	dup2(cmd_i->out_fd, STDOUT_FILENO);
	if (cmd_i->cmd_stat || cmd_i->in_fd < 0)
	{
		cmd_error(cmd_i);
		exit (EXIT_FAILURE);
	}
	execve(cmd_i->cmd_argv[0], cmd_i->cmd_argv, envp);
	exit (EXIT_FAILURE);

}

static void	execute_cmds(char *const *envp, t_cmd *cmd_i)
{
	int		status;
	pid_t	pid;

	dup2(cmd_i->in_fd, STDIN_FILENO);
	close(cmd_i->in_fd);
	pid = fork();
	if (pid == 0)
		execute_child(envp, cmd_i);
	close(cmd_i->out_fd);
	status = 0;
	// waitpid(pid, &status, WNOHANG);
	waitpid(pid, &status, 0);
	return ;
}

void	execute(t_main_cont *cont, char *const *envp)
{
	int		i;

	i = 0;
	while (i < cont->nb_cmds)
	{
		if (i == cont->nb_cmds - 1 && cont->first_cmd[i].out_fd < 0)
		{
			file_error(cont->out_file);
			break;
		}
		execute_cmds(envp, &(cont->first_cmd[i]));
		i++;
	}
	return ;
}