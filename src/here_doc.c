#include "../incl/pipex.h"
<<<<<<< HEAD
#include "get_next_line.h"
=======
>>>>>>> ef6dd6201264f006a88f0f681d97019b4524f05e

void	read_heredoc(char *delimiter)
{
	int		heredoc_fd;
	char	*buffer;
	
	heredoc_fd = open(HEREDOC, O_TRUNC | O_CREAT | O_CLOEXEC | O_RDWR, 0644);
	write(STDOUT_FILENO, "pipe heredoc> ", sizeof"pipe heredoc> ");
	while (1)
	{
		buffer = get_next_line(STDIN_FILENO);
		if (!buffer)
		{
			sleep(1);
			continue ;
		}
		else if (!strncmp(buffer, delimiter, strlen(buffer) - 1))
			break;
		else
			write(STDOUT_FILENO, "pipe heredoc> ", sizeof"pipe heredoc> ");
		write(heredoc_fd, buffer, ft_strlen(buffer));
		if (buffer)
			free (buffer);
	}
<<<<<<< HEAD
=======
	perror("here_doc finished");
>>>>>>> ef6dd6201264f006a88f0f681d97019b4524f05e
	free (buffer);
	close(heredoc_fd);
	return ;
}
