/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pipex.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iyahoui- <iyahoui-@student.42quebec.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/27 22:46:20 by iyahoui-          #+#    #+#             */
/*   Updated: 2022/02/01 19:37:51 by iyahoui-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incl/pipex.h"

int main(int argc, char **argv, char **envp)
{
	t_main_cont	container;	//main container declared on the stack
	t_error		main_status;

	printf("get_file_mode(\"/usr/bin/sort\") : %d\n", get_file_mode("/usr/bin/sort"));
	printf("get_file_mode(\"/usr/bin/uniq\") : %d\n", get_file_mode("/usr/bin/uniq"));
	printf("!access(/usr/bin/uniq, F_OK) : %d\n", !access("/usr/bin/sort", F_OK));
	printf("!access(/usr/bin/uniq, F_OK) : %d\n", !access("/usr/bin/uniq", F_OK));
	//check_argc will exit(EXIT_FAILURE) on error;
	check_argc(argc);
	
	main_status = init(&container, argc);
	// ERROR HANDLING
	
	// printf("\n***** parse_test after init() *****\n");
	// parse_test(&container);
	
	main_status = parse(&container, argc, argv, envp);

	printf("\n***** parse_test after parse() *****\n");
	parse_test(&container);
	// ERROR HANDLING

	// main_status = redirect_in_file(container.first_cmd, container.in_file);
	// ERROR HANDLING

	// main_status = execute(container.first_cmd, envp);
	// ERROR HANDLING

	// main_status = cleanup(&container);
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
 * 			1:1 relationship btw a flag's position and the amount of bits by which it needs 
 * 			to be shifted (from 0x1)
 * 
 */
