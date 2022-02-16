/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cleanup.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iyahoui- <iyahoui-@student.42quebec.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/08 20:19:53 by iyahoui-          #+#    #+#             */
/*   Updated: 2022/02/15 20:30:57 by iyahoui-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

static void	free_main_cont(t_main_cont *cont)
{
	int	i;

	if (cont->pathv)
		ft_free_split(cont->pathv);
	free (cont->in_file->filepath);
	free (cont->in_file);
	free (cont->out_file->filepath);
	free (cont->out_file);
	i = 0;
	while (cont->first_cmd && i < cont->nb_cmds)
	{
		if (cont->first_cmd[i].cmd_argv)
			ft_free_split(cont->first_cmd[i].cmd_argv);
		i++;
	}
	free (cont->first_cmd);
	free (cont->child_pids);
}

void	close_fds(t_main_cont *cont)
{
	int	i;

	i = 0;
	if (!ft_strncmp(cont->in_file->filepath, HEREDOC, sizeof(HEREDOC)))
		unlink(HEREDOC);
	while (i < cont->nb_cmds)
	{
		close(cont->first_cmd[i].in_fd);
		close(cont->first_cmd[i].out_fd);
		i++;
	}
	return ;
}

void	cleanup(t_main_cont *cont)
{
	close_fds(cont);
	free_main_cont(cont);
	return ;
}
