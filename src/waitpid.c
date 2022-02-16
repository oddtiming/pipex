#include "pipex.h"

void	add_waitpid(t_main_cont *cont, int pid)
{
	static int i;

	cont->child_pids[i] = pid;
	i++;
	return ;
}
