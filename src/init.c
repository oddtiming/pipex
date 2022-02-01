/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iyahoui- <iyahoui-@student.42quebec.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/27 22:46:34 by iyahoui-          #+#    #+#             */
/*   Updated: 2022/01/31 20:12:25 by iyahoui-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incl/pipex.h"

t_error	init(t_main_cont *container, char **argv, int argc)
{
	t_error	init_status;

	init_status = init_container(container, argc - 3); //2 for files + 1 for argv[0]
	if (init_status)
		return (init_status);
	init_status = init_cmds(container->first_cmd, argv, container->nb_cmds);
	if (init_status)
		return (init_status);
	return (0);
}

t_error	init_container(t_main_cont *container, int nb_cmds)
{
	container->in_file = malloc(sizeof(t_file));
	if (!container->in_file)
		return (E_MALLOC);
	ft_bzero((void *) container, sizeof(t_main_cont));
	container->nb_cmds = nb_cmds;
	container->out_file = malloc(sizeof(t_file));
	if (!container->out_file)
		return (E_MALLOC);
	container->pathv = malloc(sizeof(char **));
	if (!container->pathv)
		return (E_MALLOC);
	container->first_cmd = malloc(container->nb_cmds * sizeof(t_cmd));
	if (!container->first_cmd)
		return (E_MALLOC);

	return (0);
}

t_error	init_cmds(t_cmd *first_cmd, char **argv, size_t nb_cmds)
{
	t_cmd	*cmd_i;
	size_t	i;
	int		pipe_fds[2];

	i = 0;
	while (i < nb_cmds)
	{
		cmd_i = first_cmd + i;
		if ( i < (nb_cmds - 1) && pipe( pipe_fds + (2*i) ) )
			return(E_PIPE);
		//First command will have its in_fd redirected from in_file
		if (i > 0)
			cmd_i->in_fd = *(pipe_fds + 2*i);
		//Last command will have its out_fd redirected from out_file
		if (i < nb_cmds - 1)
			cmd_i->out_fd = *(pipe_fds + 2*i + 1);
		i++;
	}
	return (0);
}
