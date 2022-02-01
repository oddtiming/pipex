/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iyahoui- <iyahoui-@student.42quebec.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/27 22:46:34 by iyahoui-          #+#    #+#             */
/*   Updated: 2022/02/01 18:34:56 by iyahoui-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incl/pipex.h"

t_error	init(t_main_cont *container, int argc)
{
	t_error	init_status;

	init_status = init_container(container, argc - 3); //2 for files + 1 for argv[0]
	if (init_status)
		return (init_status);
	init_status = init_cmds(container->first_cmd, container->nb_cmds);
	if (init_status)
		return (init_status);
	return (0);
}

t_error	init_container(t_main_cont *container, int nb_cmds)
{
	container->in_file = malloc(sizeof(t_file));
	if (!container->in_file)
		return (E_MALLOC);
	container->nb_cmds = nb_cmds;
	container->out_file = malloc(sizeof(t_file));
	container->pathv = malloc(sizeof(char **));
	container->first_cmd = malloc(container->nb_cmds * sizeof(t_cmd));
	if (!container->out_file || !container->pathv || !container->first_cmd)
		return (E_MALLOC);

	return (0);
}

t_error	init_cmds(t_cmd *first_cmd, size_t nb_cmds)
{
	t_cmd	*cmd_i;
	size_t	i;
	int		pipe_fds[2];

	if (pipe(pipe_fds))
		return (E_PIPE);
	first_cmd->out_fd = pipe_fds[1];
	i = 1;
	while (i < nb_cmds)
	{
		cmd_i = first_cmd + i;
		cmd_i->in_fd = pipe_fds[0];
		if (pipe(pipe_fds))
			return(E_PIPE);
		if (i != nb_cmds - 1)
			cmd_i->out_fd = pipe_fds[1];
		i++;
	}
	cmd_i = first_cmd + i;
	cmd_i->in_fd = pipe_fds[0];
	return (0);
}
