#include "../incl/pipex.h"

int main(int argc, char **argv, char **envp)
{
	t_main_cont	container;	//main container declared on the stack
	t_error		main_status;

	//check_argc will exit(EXIT_FAILURE) on error;
	check_argc(argc);
	if (!strncmp(argv[1], HEREDOC, sizeof(HEREDOC)))
	{
		read_heredoc(argv[2]);
		// container.in_file->filepath = ft_strdup(HEREDOC);
	}
	// return (0);
	main_status = init(&container, argc);
	// ERROR HANDLING
	
	// printf("\n***** parse_test after init() *****\n");
	// parse_test(&container);
	
	main_status = parse(&container, argc, argv, envp);

	// ERROR HANDLING

	main_status = redirect(&container);
	// ERROR HANDLING
	printf("\n***** parse_test after redirect() *****\n");
	parse_test(&container);

	execute(&container, envp);
	// ERROR HANDLING

	// container.in_file->filepath = HEREDOC;
	cleanup(&container);
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
