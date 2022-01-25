#include "../incl/pipex.h"

static int	execute_cmd_n(t_args *args, int cmd_index)
{
	int		i;
	char	*cmd_path;
	char	*cmd_ptr;

	if (cmd_index == 0)
		printf("exec_cmd_n: sort has entered the chat\n");
	i = 0;
	/**
	 * The idea here is to take the first token of the current command's array of strings (i.e. the first string, the name of the command)
	 * and try to match it to all the instances of the path vector.
	 * 
	 * cmd_ptr is there to represent that first string, so it needs to be appended to all elements of pathv until
	 * one is found where the command can be executed.
	 * e.g. : 	pathv = {"/bin", "/usr/bin", 0}
	 * 			cmds[cmd_index][0] = "sort"
	 * 			try execve("/bin/sort")	
	 * 				--yes?-->	executes
	 * 				--no?--->	try execve("/usr/bin/sort")
	 * 								--yes?--> executes
	 * 								--no?---> returns (-1)	//all paths are exhausted
	 * 
	 */
	cmd_ptr = ft_strdup(args->cmds[cmd_index][0]);
	while (args->pathv[i])
	{
		cmd_path = ft_strjoin(args->pathv[i], cmd_ptr);
		args->cmds[cmd_index][0] = cmd_path;
		printf("exec_cmd_n: cmd_path = %s and args->cmds[cmd_index][0] = %s\n", cmd_path, args->cmds[cmd_index][0]);
		execve(cmd_path, args->cmds[cmd_index], args->envp_ptr);
		//This will only be reached if execve() fails
		args->cmds[cmd_index][0] = cmd_ptr;
		free(cmd_path);
		i++;
	}
	//This will only be reached if execve() fails
	return (-1);
}

void	pipex_execute_cmds(t_args *args)
{
	static int	cmd_index;
	int			pipe_fds[2];
	int			status;
	pid_t		pid_wait;
	pid_t		pid_child;

	if (cmd_index < (args->cmds_count - 1))
	{
		pipe(pipe_fds);
		//write the file-redirected stream
	}
	pid_child = fork();
	if (pid_child == 0)
	{
		dup2(STDOUT_FILENO, pipe_fds[1]);
		dup2(pipe_fds[0], STDIN_FILENO);
		close(pipe_fds[0]);
		execute_cmd_n(args, cmd_index);
	}
	close(pipe_fds[1]);
	close(pipe_fds[0]);
	pid_wait = waitpid(pid_child, &status, 0);
	if (cmd_index == args->cmds_count - 1)
	{
		return ;
	}
	cmd_index+=1;

}

/**
 * @brief This function is a simple way for me to test a simpler case of executing cmds with pipes.
 * 			Since this is the base case, only a single pipe and 2 I/O redirections should be used
 * 
 * @param args the struct holding the parsed arguments passed to the program
 */
void	pipex_execute_cmd1(t_args *args)
{
	pid_t	pid_child;
	pid_t	pid_wait;
	int		status;
	int		pipe_fds[2];

	printf("reached exec_cmd1\n");
	//Create the single pipe that will allow our two commands to communicate
	pipe(pipe_fds);
	pid_child = fork();
	if (pid_child == 0)
	{
		close(pipe_fds[0]);
		dup2(pipe_fds[1], STDOUT_FILENO);
		close(pipe_fds[1]);
		execute_cmd_n(args, 0);
		printf("cmd1 failed\n");
	}
	close(pipe_fds[1]);
	pid_wait = waitpid(pid_child, &status, WUNTRACED);
	pipex_execute_cmd2(args, pipe_fds[0]);				//Pass the reading end of the fd t

}

/**
 * @brief In this simplified use case, this function receives the fd of the read end of 
 * the pipe from the previously executed command.
 * 
 * @param args 
 * @param read_end_fd 
 */
void	pipex_execute_cmd2(t_args *args, int read_end_fd)
{
	pid_t	pid_child;
	pid_t	pid_wait;
	int		status;

	//Now the output of cmd1 is sitting tight in the pipe, waiting for cmd2 to execute it
	pid_child = fork();
	if (pid_child == 0)
	{
		pipex_redirect_out_file(args);
		dup2(read_end_fd, STDIN_FILENO);
		close(read_end_fd);
		execute_cmd_n(args, 1);
		printf("cmd2 failed\n");
	}
	close(read_end_fd);
	pid_wait = waitpid(pid_child, &status, WUNTRACED);
	printf("test(end of pipex_exec_cmd2)\n");
	return ;
}
