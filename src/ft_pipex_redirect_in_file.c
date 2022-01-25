#include "../incl/pipex.h"

void	pipex_redirect_in_file(t_args *args)
{
	int	status;
	int	fdin;

	printf("in redirect_in_file, args->in_file = %s\n", args->in_file);
	status = access(args->in_file, F_OK);
	if (status)
	{
		write(2, "pipex: in_file does not exist\n", ft_strlen("pipex: in_file does not exist\n"));
		// pipex_cleanup_args(args);
		//todo: properly handle error reporting
		exit(2);
	}
	fdin = open(args->in_file, O_RDONLY);
	//Redirect in_file onto stdin
	dup2(fdin, STDIN_FILENO);
	
	//Now we can close fdin
	close(fdin);
	return ;
}

void	pipex_redirect_out_file(t_args *args)
{
	int	fdout;

	fdout = open(args->out_file, O_CREAT | O_TRUNC | O_WRONLY | O_CLOEXEC, 0644);
	dup2(fdout, STDOUT_FILENO);
	close (fdout);
	return ;
}