#include "../incl/pipex.h"

t_error	redirect_in_file(t_main_cont *cont)
{
	int	fd;

	fd = open(cont->in_file->filepath, O_RDONLY);
	cont->first_cmd->in_fd = fd;
	return (0);
}

t_error	redirect_out_file(t_main_cont *cont)
{
	int		fd;
	char	*file;

	file = cont->out_file->filepath;
	if (ft_strncmp(cont->in_file->filepath, HEREDOC, 8))
		fd = open(file, O_TRUNC | O_CREAT | O_WRONLY | O_CLOEXEC, 0644);
	else
	{
		if (cont->out_file->access_flags & F_OK)
			fd = open(file, O_APPEND | O_WRONLY);
		else
			fd = open(file, O_CREAT | O_EXCL | O_APPEND | O_WRONLY, 0644);
	}
	cont->first_cmd[cont->nb_cmds - 1].out_fd = fd;
	return (0);
}

t_error	redirect(t_main_cont *cont)
{
	t_error	status;

	status = redirect_in_file(cont);

	status = redirect_out_file(cont);

	return (status);
}