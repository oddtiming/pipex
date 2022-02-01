#include "../incl/pipex.h"
#include <string.h>

int main(int argc, char const *argv[], char const *envp[])
{
	t_main_cont	container;
	t_cmd				*cmd1;
	char				*temp_ptr;

	cmd1 = malloc(2 * sizeof(t_cmd));
	cmd1->cmd_file->filepath = strdup("bli");
	(cmd1 + 1)->cmd_file->filepath = strdup("bla");
	container.first_cmd = cmd1;
	
	printf("cmd1 = %s\n", container.first_cmd->cmd_file->filepath);

	//Let's see how pointer arithmetic works for big structs
	temp_ptr = (cmd1 + 1)->cmd_file;
	printf("cmd2 = %s\n", temp_ptr);
	printf("cmd2 = %s\n", container.first_cmd[1].cmd_file->filepath);

	free(cmd1->cmd_file);
	free((cmd1 + 1)->cmd_file->filepath);
	free(cmd1);
	return (0);
}
