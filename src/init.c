/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iyahoui- <iyahoui-@student.42quebec.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/27 22:46:34 by iyahoui-          #+#    #+#             */
/*   Updated: 2022/02/15 20:50:20 by iyahoui-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

t_error	init(t_main_cont *container, int argc)
{
	t_error	init_status;

	init_status = init_container(container, argc - 3);
	if (init_status)
		return (init_status);
	init_status = init_cmds(container->first_cmd, container->nb_cmds);
	ft_putstr_fd("finished init_cmds\n", 2);
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
	if (!container->out_file)
		return (E_MALLOC);
	container->first_cmd = malloc(container->nb_cmds * sizeof(t_cmd));
	if (!container->first_cmd)
		return (E_MALLOC);
	container->child_pids = malloc(container->nb_cmds * sizeof(int));
	if (!container->child_pids)
		return (E_MALLOC);
	ft_memset(&(container->child_pids), 0, container->nb_cmds);
	// ft_memset(container, 0, sizeof(container));
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
	while (i < nb_cmds - 1)
	{
		cmd_i = first_cmd + i;
		cmd_i->in_fd = pipe_fds[0];
		if (pipe(pipe_fds))
			return (E_PIPE);
		if (i != nb_cmds - 1)
			cmd_i->out_fd = pipe_fds[1];
		i++;
	}
	cmd_i = first_cmd + i;
	cmd_i->in_fd = pipe_fds[0];
	return (0);
}
