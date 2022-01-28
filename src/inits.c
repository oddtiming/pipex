#include "../incl/pipex.h"

t_status	init_container(t_main_container *container)
{
	t_status	stat_ctr_init;

	stat_ctr_init = 0;
	container->in_file = malloc(sizeof(t_file));
	//ERROR HANDLING
	container->out_file = malloc(sizeof(t_file));
	//ERROR HANDLING
	container->pathv = malloc(sizeof(char **));
	//ERROR HANDLING
	container->first_cmd = malloc(container->nb_cmds * sizeof(t_cmd));

	ft_bzero((void *) container, sizeof(t_main_container));
	
	return (stat_ctr_init);
}

t_status	init_file(t_file *file_struct, char *filepath)
{
	t_status	stat_file;
	
	stat_file = 0;
	file_struct = malloc(sizeof(t_file));
	//ERROR HANDLING
	file_struct->filepath = ft_strdup(filepath);
	if (!file_struct->filepath)
		stat_file = E_MALLOC;
	//ERROR HANDLING
	
	if (!access(filepath, F_OK))
		file_struct->access_flags |= F_EXISTS;
	if (!access(filepath, R_OK))
		file_struct->access_flags |= F_CANREAD;
	if (!access(filepath, W_OK))
		file_struct->access_flags |= F_CANWRITE;
	if (!access(filepath, X_OK))
		file_struct->access_flags |= F_CANEXEC;
}
