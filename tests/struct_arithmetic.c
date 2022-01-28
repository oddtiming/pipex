#include "../incl/pipex.h"
#include <string.h>


int main(int argc, char const *argv[], char const *envp[])
{
	t_main_container	container;
	t_cmd				*cmd1;
	char				*temp_ptr;

	cmd1 = malloc(2 * sizeof(t_cmd));
	cmd1->cmd_file.filepath = strdup("bli");
	(cmd1 + 1)->cmd_file.filepath = strdup("bla");
	container.cmd1 = cmd1;
	
	printf("cmd1 = %s\n", container.cmd1->cmd_file.filepath);

	//Let's see how pointer arithmetic works for big structs
	temp_ptr = (cmd1 + 1)->cmd_file.filepath;
	printf("cmd2 = %s\n", temp_ptr);
	printf("cmd2 = %s\n", container.cmd1[1]->cmd_file.filepath);

	free(cmd1->cmd_file.filepath);
	free((cmd1 + 1)->cmd_file.filepath);
	free(cmd1);
	return (0);
}
