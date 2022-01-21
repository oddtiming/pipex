#include "../incl/pipex.h"

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
	t_args	*args;
	// int		status;

	//to remove
	(void) argc;
	(void) argv;
	(void) envp;
	//end of remove
	argc_check(argc);
	pipex_parse_args(args, argc, argv, envp);
	pipex_redirect_in_file(args);
	// pipex_execute_cmds(args);
	// pipex_redirect_out_file(args);
	// pipex_cleanup(args);
	// status = ft_exec(&rgs, 1);
	if (args->in_file)
		printf("args->in_file after memset= %s\n", args->in_file);
	else
		printf("args->in_file has not been set\n");
	// access_test(args);
	return (errno);
}

/**
 * (19/01/22)
 * List of proceedings:
 * 	1. Parse the arguments
 * 		a. [x] Check return value of access(input_file, F_OK)
 * 		b. [x] init struct with args_init()
 * 		c. [x] Parse arguments onto respective struct variables
 * 	2. Redirect in_file > stdin
 *		a. [x] open(in_file, O_RDONLY);
 *		b. [x] dup2(in_file_fd, STDIN_FILENO);
 *		c. [x] close(in_file_fd);
 *	3. Execute cmds[n]
 *		a. [] pipe(pipe_fds);
 *		b. [] fork()
 *		c. [] child: dup2(pipe_fds[0], STDIN_FILENO); close(pipe_fds); execve cmd_n;
 *		d. [] parent: waitpid(pid_child); execute cmds(cmds[n+1]); //Could also simply return, and the calling process calls the function again with n+1.
 * 	4. Redirect stdout > out_file
 * 		a. [] open(out_file, O_TRUNC | O_CREAT | O_WRONLY)
 * 		b. [] dup2(out_file, STDOUT_FILENO) //Or is it the opposite??? I'm iffy on that one, TODO
 * 		c. [] close;
 * 	5. Clean up and return
 * 		a. [] [I] create a malloc function with a hash table that knows if a certain variable has been malloced before, ideally by address
 * 		b. [] Close all fds
 * 		c. [] Free all the struct's elements
 * 	
 */