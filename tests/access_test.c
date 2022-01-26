#include "../libft/libft.h"
#include <stdio.h>
#include <unistd.h>
#include <errno.h>

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

char	*ft_get_last_token(char *string, char delimiter)
{
	size_t	str_len;
	char	*last_token;
	size_t	i;
	size_t	j;

	str_len = ft_strlen(string);
	i = str_len;
	while (string[i] != delimiter && i >= 0)
		i--;
	last_token = malloc(str_len - i + 1);
	j = 0;
	while (i++ < str_len)
	{
		last_token[j] = string[i];
		j++;
	}
	last_token[j] = 0;
	return (last_token);
}

int	main(int argc, char *argv[], char *envp[])
{
//	int		infile_fd;
	int		status;
	char	*shell_version;
	char	*buff;

	(void) argc;
	(void) argv;
	(void) envp;
	status = access(argv[1], F_OK);
	buff = get_env_var(envp, "SHELL");
	shell_version = ft_get_last_token(buff, '/');
	free (buff);

	printf("errno = %d\n", errno);
	printf("shell = %s\n", shell_version);
	perror(shell_version);
	free(shell_version);
	return (0);
}