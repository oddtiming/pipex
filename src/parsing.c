#include "../incl/pipex.h"
#include "../libft/libft.h"

void	args_init(t_args *args)
{
	args = malloc(sizeof(t_args));
	ft_bzero(args, sizeof(t_args));
}

void	parse_args(t_args *args, int argc, char const *argv[], char const *envp[])
{
	char	*path_full;
	
	if (argc < ARGS_NUMBER)
		write(2, "pipex: wrong number of arguments\n", 35);
	args->in_file = ft_strdup(argv[1]);
	path_full = get_env_var(envp, "PATH");
}