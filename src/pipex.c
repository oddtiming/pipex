/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iyahoui- <iyahoui-@student.42quebec.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/08 20:19:16 by iyahoui-          #+#    #+#             */
/*   Updated: 2022/02/09 13:08:22 by iyahoui-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int	main(int argc, char **argv, char **envp)
{
	t_main_cont	container;
	t_error		main_status;

	check_args(argc, argv);
	ft_memset(&container, 0, sizeof(container));
	main_status = 0;
	if (!strncmp(argv[1], "here_doc", sizeof("here_doc")))
		main_status |= heredoc(&container, argc, argv[2]);
	else
		main_status |= init(&container, argc);
	if (main_status)
		pipex_error(main_status);
	main_status |= parse(&container, argc, argv, envp);
	if (main_status & (E_SPLIT | E_MALLOC | E_ENVPATH))
		pipex_error(main_status);
	redirect(&container);
	main_status = execute(&container, envp);
	if (main_status || !(container.out_file->access_flags & F_CANWRITE))
		exit (1);
	cleanup(&container);
	return (0);
}
