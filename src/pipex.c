#include "../incl/pipex.h"
#include "../libft/libft.h"

int main(int argc, char const *argv[], char const *envp[])
{
	t_args	args;
	int		status;

	//to remove
	(void) argc;
	(void) argv;
	(void) envp;
	//end of remove
	args_init(&args);
	parse_args(&args, argc, argv, envp);
	status = ft_exec(&args, 1);
	printf("args.in_file after memset= %s\n", args.in_file);
	// access_test(&args);
	return (errno);
}
