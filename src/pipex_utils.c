//Note: everything in this file should be given its own .c file in the libft submodule
#include "../incl/pipex.h"
#include "../libft/libft.h"

//This fct needs reviewing, I do not like how it handles memory allocation and its potential failure.
//See Notion page for more details
char	*get_env_var(char const *envp[], char *var_name)
{
	int	var_strlen;
	int	envp_strlen;
	int	i;
	char	*var_val;

	i = 0;
	if (var_name)
		var_strlen = ft_strlen(var_name);
	while (envp[i])
	{
		if (!ft_strncmp(envp[i], var_name, var_strlen))
		{
			envp_strlen = ft_strlen(envp[i]);
			var_val = malloc(envp_strlen - var_strlen);
			var_val = ft_strncpy(var_val, (char *)envp[i] + var_strlen + 1, envp_strlen - var_strlen);
			return (var_val);
		}
		i++;
	}
	//allocate heap memory in case of failure to make sure that the return value can be freed
	var_val = malloc(1);
	return (var_val);
}

void	ft_print_split(char **split_arr, char *name)
{
	int	i;

	i = 0;

	while (split_arr && split_arr[i])
	{
		printf("{%s} split_arr[%d] = \"%s\"\n", name, i, split_arr[i]);
		i++;
	}
	return ;
}

void	ft_strcat_iter(char **vector, char *to_cat)
{
	int	i;

	i = 0;
	while (vector && vector[i])
	{
		vector[i] = ft_strjoin_free(vector[i], to_cat);
		i++;
	}
	return ;
}