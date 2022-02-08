#include "../incl/pipex.h"

static void	read_heredoc(char *delimiter, int heredoc_fd)
{
	char	*buffer;

	write(STDOUT_FILENO, "pipe heredoc> ", sizeof"pipe heredoc> ");
	while (1)
	{
		buffer = get_next_line(STDIN_FILENO);
		if (!buffer)
			continue ;
		else if (!strncmp(buffer, delimiter, ft_strlen(buffer) - 1) && \
					ft_strlen(buffer) > 1)
			break;
		else
			write(STDOUT_FILENO, "pipe heredoc> ", sizeof"pipe heredoc> ");
		write(heredoc_fd, buffer, ft_strlen(buffer));
		if (buffer)
			free (buffer);
	}
	close(heredoc_fd);
	free (buffer);
	exit (0);
}

void	heredoc(char *delimiter)
{
	int		heredoc_fd;
	int		status;
	pid_t	pid;
	
	status = 0;
	heredoc_fd = open(HEREDOC, O_TRUNC | O_CREAT | O_CLOEXEC | O_RDWR, 0644);
	pid = fork();
	if (pid == 0)
	{
		read_heredoc(delimiter, heredoc_fd);
	}
	waitpid(pid, &status, 0);
	close(heredoc_fd);
	return ;
}
