/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   inits.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iyahoui- <iyahoui-@student.42quebec.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/27 22:46:34 by iyahoui-          #+#    #+#             */
/*   Updated: 2022/01/27 23:06:50 by iyahoui-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incl/pipex.h"

t_status	init_container(t_main_container *container)
{
	container->in_file = malloc(sizeof(t_file));
	if (!container->in_file)
		return (E_MALLOC);
	container->out_file = malloc(sizeof(t_file));
	if (!container->out_file)
		return (E_MALLOC);
	container->pathv = malloc(sizeof(char **));
	if (!container->pathv)
		return (E_MALLOC);
	container->first_cmd = malloc(container->nb_cmds * sizeof(t_cmd));
	if (!container->first_cmd)
		return (E_MALLOC);

	ft_bzero((void *) container, sizeof(t_main_container));
}

t_status	init_file(t_file *file_struct, char *filepath)
{
	file_struct->filepath = ft_strdup(filepath);
	if (!file_struct->filepath)
		return (E_MALLOC);

	file_struct->access_flags |= (!access(filepath, F_OK)) << 0;
	if (errno)
		return (E_ACCFAIL);
	file_struct->access_flags |= (!access(filepath, R_OK)) << 1;
	file_struct->access_flags |= (!access(filepath, W_OK)) << 2;
	file_struct->access_flags |= (!access(filepath, X_OK)) << 3;

	(void) (e_flag & F_EXISTS) && strerror(errv[E_MALLOC << bctod(E_MALLOC)]));
	return (0);
}
