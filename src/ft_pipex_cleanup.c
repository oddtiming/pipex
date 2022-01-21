#include "../incl/pipex.h"

void	pipex_cleanup_args(t_args *args)
{
	int	i;

	i = 0;
	if (args->in_file)
		free(args->in_file);
	if (args->out_file)
		free(args->out_file);
	if (args->pathv)
		ft_free_split(args->pathv);
	while (args->cmds && args->cmds[i])
	{
		ft_free_split(args->cmds[i]);
		i++;
	}
	return ;
}