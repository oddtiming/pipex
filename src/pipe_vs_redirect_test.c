#include "../incl/pipex.h"

int	main(int argc, char const *argv[], char *envp[])
{
	int			fd_in;
	int			status;
	int			pipe_fds[2];
	char		*exec_argv[] = {"/usr/bin/sort", 0};
	pid_t		pid_child;

	(void)argc;
	(void)argv;
	fd_in = open("./files/colors.txt", O_RDONLY);
	pipe(pipe_fds);
	dup2(fd_in, STDIN_FILENO);
	pid_child = fork();
	if (pid_child == 0)
	{
		// dup2(pipe_fds[0], STDIN_FILENO);
		// close(pipe_fds[0]);
		// close(pipe_fds[1]);
		execve(exec_argv[0], exec_argv, envp);
		exit(1);
	}
	close(pipe_fds[0]);
	close(pipe_fds[1]);
	close(fd_in);
	waitpid(pid_child, &status, 0);
	printf("prout\n");
	printf("0x810202 = %d\n", 0x810202);
	return (0);
}