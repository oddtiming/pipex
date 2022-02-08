#include "../incl/pipex.h"

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
	execute(&container, envp);
	cleanup(&container);
	if (main_status)
		exit (1);
	return (0);
}
// printf("\n***** parse_test after redirect() *****\n");
// parse_test(&container);
