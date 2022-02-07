#include "../incl/pipex.h"

static void	free_main_cont(t_main_cont *cont)
{
	int	i;
	
	if (cont->pathv)
		ft_free_split(cont->pathv);
	if (cont->in_file && cont->in_file->filepath)
	{
		if (cont->in_file->filepath)
			free (cont->in_file->filepath);
		free(cont->in_file);
	}
	if (cont->out_file && cont->out_file->filepath)
	{
		if (cont->out_file->filepath)
			free (cont->out_file->filepath);
		free(cont->out_file);
	}
	i = 0;
	while (cont->first_cmd && i < cont->nb_cmds)
	{
		if (cont->first_cmd[i].cmd_argv)
			ft_free_split(cont->first_cmd[i].cmd_argv);
		i++;
	}
	if (cont->first_cmd)
		free (cont->first_cmd);
}

void	close_fds(t_main_cont *cont)
{
	int	i;

	i = 0;
<<<<<<< HEAD
	// if (!ft_strncmp(cont->in_file->filepath, HEREDOC, 8))
		unlink("./here_doc");	//DOES NOT WORK
=======
	if (!ft_strncmp(cont->in_file->filepath, HEREDOC, 8))
		unlink("./here_doc");
>>>>>>> ef6dd6201264f006a88f0f681d97019b4524f05e
	while (i < cont->nb_cmds)
	{
		close(cont->first_cmd[i].in_fd);
		close(cont->first_cmd[i].out_fd);
		i++;
	}
	return ;
}

void	cleanup(t_main_cont *cont)
{
	close_fds(cont);
	free_main_cont(cont);
	return ;
}
