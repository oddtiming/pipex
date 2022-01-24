//Note: everything in this file should be given its own .c file in the libft submodule
#include "../incl/pipex.h"

//This fct needs reviewing, I do not like how it handles memory allocation and its potential failure.
//See Notion page for more details
char	*get_env_var(char const *envp[], char *var_name)
{
	int		var_strlen;
	int		envp_strlen;
	int		i;
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

/**
 * @brief This function returns a malloced substring of the last token as delimited by param delimiter from
 * 	param string.
 * 
 * @param string	//The original string.
 * @param delimiter	//What separates each token in the string.
 * @return char*	//Malloced string of the last token. If no delimiter, a copy of the string will be returned.
 * 					//In case of error, NULL is returned.
 */
char	*ft_get_last_token(char *string, char delimiter)
{
	size_t	str_len;
	char	*last_token;
	size_t	i;
	size_t	j;

	str_len = ft_strlen(string);
	i = str_len;
	if (!string)
		return (NULL);
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

void	ft_print_split(char **split_arr, char *name)
{
	int	i;

	i = 0;
	if (!split_arr)
		return ;
	while (split_arr[i])
	{
		printf("{%s} split_arr[%d] = \"%s\"\n", name, i, split_arr[i]);
		i++;
	}
	printf("{%s} Is it null-terminated: split_arr[%d] = %s\n", name, i, split_arr[i]);
	return ;
}

//NOTE: ft_strcat_iter assumes that the array is populated by malloced strings
void	ft_strcat_iter(char **array, char *to_cat)
{
	int	i;

	i = 0;
	while (array && array[i])
	{
		array[i] = ft_strjoin_free(array[i], to_cat);
		i++;
	}
	return ;
}