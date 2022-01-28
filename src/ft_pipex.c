/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pipex.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iyahoui- <iyahoui-@student.42quebec.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/27 22:46:20 by iyahoui-          #+#    #+#             */
/*   Updated: 2022/01/27 22:48:49 by iyahoui-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incl/pipex.h"

int main(int argc, char const *argv[], char *envp[])
{
	t_main_container	container;	//main container declared on the stack
	t_status			stat_main;

	//Style could also be : 
	// if (parse_args(container, argc, argv))
	// 	error_handling("parse_args", container);
	argc_check(argc);
	container.nb_cmds = 0;		//only to prevent fuckery with mallocing of pipe_fds
	stat_main = parse_args(&container, argc, argv, envp);
	// ERROR HANDLING

	//Important note: the I/O redirections will be handled in execute_cmds
	stat_main = execute_cmds(&container.first_cmd, envp);
	// ERROR HANDLING
	
	stat_main = cleanup(&container);
	// ERROR HANDLING
	
	return (0);
}


/**
 * @brief To set flags, we can do a little sum'n like:
 * 	if (access(file, F_OK))
 * 		flag |= F_EXISTS
 * 	
 * or do it a little more fancy:
 * typedef enum	s_fflags
 * {
 * 		F_EXISTS	= 0x01,
 * 		F_CANREAD	= 0x02,
 * 		F_CANWRITE	= 0x04,
 * 		F_CANEXEC	= 0x08
 * }	t_fflags;
 * 	flag |= (F_EXISTS & (access(file, F_OK) ^ 0x1)<<(F_EXISTS - 1))
 * 	
 * 			For that, I need to run some tests to see how members of an enum are accessed, b/c 
 * 			I could run them in a loop until I reach the end of the enum, with a very neat 
 * 			1:1 relationship btw a flag's position and the amount of bits by which it needs to be shifted (from 0x1)
 * 			c
 * 
 */