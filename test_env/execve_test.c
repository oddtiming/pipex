#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include "../libft/libft.h"

char	*get_env_var(char *envp[], char *var_name)
{
	int	var_strlen;
	int	envp_strlen;
	int	i;
	char	*var_val;

	i = 0;
	if (var_name)
		var_strlen = strlen(var_name);
	while (envp[i])
	{
		if (!strncmp(envp[i], var_name, var_strlen))
		{
			envp_strlen = strlen(envp[i]);
			var_val = malloc(envp_strlen - var_strlen);
			var_val = strncpy(var_val, envp[i] + var_strlen + 1, envp_strlen - var_strlen);
			return (var_val);
		}
		i++;
	}
	//allocate heap memory in case of failure to make sure that the return value can be freed
	var_val = malloc(1);
	return (var_val);
}

int	main(int argc, char *argv[], char *envp[])
{
	int	infile_fd;
//	int	pipe_fds[2];
	char	*path;
	char	*path_array[] = {"Users/ismaelyahyaouiracine/perl5/bin", "/usr/local/bin", "/usr/bin",  "/bin", "/usr/sbin", "/sbin", (char *)0};
//	char	*argv_duplicate[] = {"ls", "-h", "-a", NULL};
//	char	*env_args[] = {"PATH=/bin", NULL};

	(void)argc;
	(void)argv;
	//test to see if I can extract the path from envp
	path = get_env_var(envp, "PATH");
	printf("path = %s\n", path);
//	path_array = ft_split(path, ':');
//	free(path_array[2]);
//	path_array[2] = ft_strdup("/usr/bin");
//	printf("path_array[2] = %s\n", path_array[2]);
	free(path);
	for (int j = 0; path_array[j]; j++)
	{
	//	printf("path_array[%d] = %s\n", j, path_array[j]);
		//+2, one for extra "/", and other for null-termination
		path = malloc(strlen(argv[2]) + strlen(path_array[j]) + 2);
		path = strcat(path_array[j], "/");
		path = strcat(path, argv[2]);
		printf("attempted path #%d = '%s'\n", j, path);
		execve(path, NULL, envp);
		free(path);
	}

	infile_fd = open(argv[1], O_RDONLY);
	dup2(infile_fd, STDIN_FILENO);
	close(infile_fd);
	printf("at main, before execve, argc == %d\n", argc);
//	if (argc != 2)
//		exit(-1);
	printf("argv[1] = %s\n", argv[1]);
//	execve("/usr/bin/sort", NULL, envp);
	printf("execve failed");
	perror("eeeeeuh");
	return (0);
}
