#include "../incl/pipex.h"
#include "../libft/libft.h"

int main(int argc, char const *argv[], char const *envp[])
{
	t_args	args;

	args_init(&args);
	printf("size of args = %lu\n", sizeof(args));
	parse_args(&args, argc, argv, envp);
	return (errno);
}