#include "../incl/pipex.h"
#include "../libft/libft.h"

#include <ctype.h>

static void	argc_check(int argc)
{
	if (argc < ARGC_MIN)
	{
		write(2, "pipex: wrong # of args, pal.\n", ft_strlen("pipex: wrong # of args, pal.\n"));
		//do some error handling ninja business
		exit(2);
	}
	return ;
}

int main(int argc, char const *argv[], char const *envp[])
{
	t_args	args;
	// int		status;

	//to remove
	(void) argc;
	(void) argv;
	(void) envp;
	//end of remove
	argc_check(argc);
	parse_args(&args, argc, argv, envp);
	// status = ft_exec(&args, 1);
	printf("args.in_file after memset= %s\n", args.in_file);
	// access_test(&args);
	return (errno);
}

/**
 * (19/01/22)
 * List of proceedings:
 * 	1. Parse the arguments
 * 		a. Check return value of access(input_file, F_OK)
 * 		b. init struct with args_init()
 * 		c. Parse arguments onto respective struct variables
 * 	2. Redirect in_file > stdin
 *		a. open(in_file, O_RDONLY);
 *		b. dup2(in_file_fd, STDIN_FILENO);
 *		c. close(in_file_fd);
 *	3. Execute cmds[n]
 *		a. pipe(pipe_fds);
 *		b. fork()
 *		c. child: dup2(pipe_fds[0], STDIN_FILENO); close(pipe_fds); execve cmd_n;
 *		d. parent: waitpid(pid_child); execute cmds(cmds[n+1]); //Could also simply return, and the calling process calls the function again with n+1.
 * 	4. Redirect stdout > out_file
 * 		a. open(out_file, O_TRUNC | O_CREAT | O_WRONLY)
 * 		b. dup2(out_file, STDOUT_FILENO) //Or is it the opposite??? I'm iffy on that one, TODO
 * 		c. close;
 * 	5. Clean up and return
 * 		a. [I] create a malloc function with a hash table that knows if a certain variable has been malloced before, ideally by address
 * 		b. Close all fds
 * 		c. Free all the struct's elements
 * 	
 */