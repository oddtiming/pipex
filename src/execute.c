/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iyahoui- <iyahoui-@student.42quebec.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/08 20:20:00 by iyahoui-          #+#    #+#             */
/*   Updated: 2022/02/08 20:20:01 by iyahoui-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

static void	execute_child(char *const *envp, t_cmd *cmd_i)
{
	int		status;

	status = 0;
	dup2(cmd_i->out_fd, STDOUT_FILENO);
	if (cmd_i->cmd_stat)
		cmd_error(cmd_i);
	if (cmd_i->cmd_stat || cmd_i->in_fd < 0)
		exit (EXIT_FAILURE);
	execve(cmd_i->cmd_argv[0], cmd_i->cmd_argv, envp);
	exit (EXIT_FAILURE);
}

static int	execute_cmds(char *const *envp, t_cmd *cmd_i)
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
	waitpid(pid, &status, 0);
	return (status);
}

int	execute(t_main_cont *cont, char *const *envp)
{
	int		status;
	int		i;

	i = 0;
	status = 0;
	while (i < cont->nb_cmds)
	{
		if (i == cont->nb_cmds - 1 && cont->first_cmd[i].out_fd < 0)
		{
			file_error(cont->out_file);
			break ;
		}
		status = execute_cmds(envp, &(cont->first_cmd[i]));
		i++;
	}
	return (status);
}
