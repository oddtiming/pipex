#include "../incl/pipex.h"

static void	read_heredoc(char *delimiter, int heredoc_fd)
{
	char	*buffer;

	while (1)
	{
		ft_putstr_fd("pipe heredoc> ", STDOUT_FILENO);
		buffer = get_next_line(STDIN_FILENO);
		if ((!strncmp(buffer, delimiter, ft_strlen(buffer) - 1) && \
					ft_strlen(buffer) > 1) || !buffer)
			break ;
		ft_putstr_fd(buffer, heredoc_fd);
		if (buffer)
			free (buffer);
	}
	close(heredoc_fd);
	free (buffer);
	exit (0);
}

t_error	heredoc(t_main_cont *cont, int argc, char *delimiter)
{
	int		heredoc_fd;
	int		status;
	pid_t	pid;

	status = 0;
	heredoc_fd = open(HEREDOC, O_TRUNC | O_CREAT | O_CLOEXEC | O_RDWR, 0644);
	pid = fork();
	if (pid == 0)
		read_heredoc(delimiter, heredoc_fd);
	waitpid(pid, &status, 0);
	close(heredoc_fd);
	return (init(cont, argc - 1));
}
