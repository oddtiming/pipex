/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iyahoui- <iyahoui-@student.42quebec.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/08 20:19:20 by iyahoui-          #+#    #+#             */
/*   Updated: 2022/02/08 20:19:21 by iyahoui-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	redirect_in_file(t_main_cont *cont)
{
	int	fd;

	fd = open(cont->in_file->filepath, O_RDONLY);
	if (fd < 0)
		file_error(cont->in_file);
	cont->first_cmd->in_fd = fd;
	return ;
}

void	redirect_out_file(t_main_cont *cont)
{
	int		fd;
	char	*file;

	file = cont->out_file->filepath;
	if (ft_strncmp(cont->in_file->filepath, HEREDOC, 8))
		fd = open(file, O_TRUNC | O_CREAT | O_WRONLY | O_CLOEXEC, 0644);
	else
	{
		if (cont->out_file->access_flags & F_EXISTS)
			fd = open(file, O_APPEND | O_WRONLY);
		else
			fd = open(file, O_CREAT | O_APPEND | O_WRONLY, 0644);
	}
	cont->first_cmd[cont->nb_cmds - 1].out_fd = fd;
	return ;
}

void	redirect(t_main_cont *cont)
{
	redirect_in_file(cont);
	redirect_out_file(cont);
	return ;
}
