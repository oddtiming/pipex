#include "../incl/pipex.h"

void	pipex_redirect_in_file(t_args *args)
{
	int	status;
	int	fdin;

	status = access(args->in_file, F_OK);
	if (status)
	{
		write(2, "pipex: in_file does not exist\n", ft_strlen("pipex: in_file does not exist\n"));
		pipex_cleanup_args(args);
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
