#include "../incl/pipex.h"

void	file_error(t_file *file)
{
	ft_putstr_fd("oh shit: ", 2);
	ft_putstr_fd(file->filepath, 2);
	if (file->access_flags == 0)
		ft_putstr_fd(": file does not exist\n", 2);
	else if (!(file->access_flags & (F_CANWRITE | F_CANREAD)))
		ft_putstr_fd(": cannot read from/write to file\n", 2);
}

void	cmd_error(t_cmd *cmd_i)
{
	ft_putstr_fd("oh shit: ", 2);
	ft_putstr_fd(cmd_i->cmd_argv[0], 2);
	if (cmd_i->cmd_stat & E_NOCMD)
		ft_putstr_fd(": command not found\n", 2);
	else if (cmd_i->cmd_stat & E_NOEXEC)
		ft_putstr_fd(": permission denied\n", 2);
}

void	pipex_error(t_error err)
{
	if (!err)
		ft_putstr_fd("pipex() done fucked up: empty pipex_error() call\n", 2);
	else if (err <= E_SPLIT)
		ft_putstr_fd("pipex() done fucked up: malloc() error\n", 2);
	else if (err & E_PIPE)
		ft_putstr_fd("pipex() done fucked up: pipe() error\n", 2);
	else if (err & E_ENVPATH)
		ft_putstr_fd("Warning: env does not contain a $PATH\n", 2);
	if (!(err == E_ENVPATH))
		exit (1);
}
