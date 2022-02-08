#include "../incl/pipex.h"

int main(int argc, char **argv, char **envp)
{
	t_main_cont	container;	//main container declared on the stack
	t_error		main_status;

	//check_argc will exit(EXIT_FAILURE) on error;
	check_argc(argc);
	ft_memset(&container, 0, sizeof(container));
	main_status = 0;
	if (!strncmp(argv[1], "here_doc", sizeof("here_doc")))
	{
		heredoc(argv[2]);
		main_status = init(&container, argc - 1);
		// container.in_file->filepath = ft_strdup(HEREDOC);
	}
	else
		main_status = init(&container, argc);
	if (main_status)
		pipex_error(main_status);
	main_status = parse(&container, argc, argv, envp);
	if (main_status && main_status <= E_PIPE)
		pipex_error(main_status);
	main_status = redirect(&container);
	execute(&container, envp);
	cleanup(&container);
	return (0);

	// ERROR HANDLING

	// container.in_file->filepath = HEREDOC;
	// ERROR HANDLING
	// printf("\n***** parse_test after redirect() *****\n");
	// parse_test(&container);
	
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
