#include "../incl/pipex.h"
#include "../libft/libft.h"

void	access_test(t_args *args)
{
	int		status;
	int		in_file_fd;
	char	*sort_args[] = {"/usr/bin/sort", "--radixsort", NULL};

	status = access(args->in_file, F_OK);
	if (status)
	{
		fprintf(stderr, "file does not exist\n");
		exit(EXIT_FAILURE);
	}
	in_file_fd = open(args->in_file, O_RDONLY);
	status = dup2(in_file_fd, STDIN_FILENO);
	execv(sort_args[0], sort_args);
	return ;
}
