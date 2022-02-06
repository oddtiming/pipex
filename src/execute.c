#include "../incl/pipex.h"

static void	execute_cmds(char *const *envp, t_cmd *cmd_i, size_t nb_cmds)
{
	int		i;
	int		status;
	pid_t	pid;

	i = 0;
	if (!nb_cmds)
		return ;
	dup2(cmd_i->in_fd, STDIN_FILENO);
	close(cmd_i->in_fd);
	pid = fork();
	if (pid == 0)
	{
		dup2(cmd_i->out_fd, STDOUT_FILENO);
		printf("entered exec_cmd with cmd_i.filepath == %s\n", cmd_i->cmd_argv[0]);
		execve(cmd_i->cmd_argv[0], cmd_i->cmd_argv, envp);
		exit (0);
	}
	close(cmd_i->out_fd);
	status = 0;
	waitpid(pid, &status, WNOHANG);
	execute_cmds(envp, cmd_i + 1, nb_cmds - 1);
	return ;
}

void	execute(t_main_cont *cont, char *const *envp)
{
	execute_cmds(envp, cont->first_cmd, cont->nb_cmds);
	return ;
}