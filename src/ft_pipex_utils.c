//Note: everything in this file should be given its own .c file in the libft submodule
#include "../incl/pipex.h"

//This fct needs reviewing, I do not like how it handles memory allocation and its potential failure.
//See Notion page for more details
char	*get_env_var(char *const *envp, char *var_name)
{
	int		var_strlen;
	int		envp_strlen;
	int		i;
	char	*var_val;

	i = 0;
	if (var_name)
		var_strlen = ft_strlen(var_name);
	else
		return (NULL);
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
	//Will only be reached if var_name is not found
	return (NULL);
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
void	ft_strcat_iter(char **vector, char *to_cat)
{
	int	i;

	i = 0;
	while (vector && vector[i])
	{
		vector[i] = ft_strjoin_free(vector[i], to_cat);
		if (!vector[i])
		{
			ft_free_split(vector);
			*vector = NULL;
			return ;
		}
		i++;
	}
	return ;
}

void	parse_test(t_args *args)
{
	char	*buff;

	buff = malloc(2);
	buff[1] = 0;
	if (args->cmds_count)
		printf("args->cmds_count = %d\n", args->cmds_count);
	else
		printf("args->cmds_count has not yet been initialized\n");
	if (args->in_file)
		printf("args->in_file = %s\n", args->in_file);
	else
		printf("args->in_file has not yet been initialized\n");
	if (args->out_file)
		printf("args->out_file = %s\n", args->out_file);
	else
		printf("args->out_file has not yet been initialized\n");
	if (args->pathv)
		ft_print_split(args->pathv, "pathv");
	else
		printf("args->pathv has not yet been initialized\n");
	if (args->envp_ptr)
		ft_print_split(args->envp_ptr, "envp_ptr");
	else
		printf("args->envp_ptr has not yet been initialized\n");
	if (args->cmds)
	{
		for (int i = 0; i < args->cmds_count; i++)
		{
			buff[0] = i + '0';
			ft_print_split(args->cmds[i], buff);
		}
	}
	else
		printf("args->cmds has not yet been initialized\n");
	free(buff);
}

#include <stdarg.h>

char	*ft_strjoin_n(size_t nb_strings, ...)
{
	va_list	ap;
	size_t	i;
	char	*joined;

	i = 0;
	va_start(ap, nb_strings);
	joined = ft_strdup(va_arg(ap, char *));
	i++;
	while (i < nb_strings)
	{
		joined = ft_strjoin_free(joined, va_arg(ap, char *));
		i++;
	}
	va_end(ap);
	return (joined);
}

void	argc_check(int argc)
{
	if (argc < _ARGC_MIN)
	{
		write(2, "pipex: wrong # of args, pal.\n", ft_strlen("pipex: wrong # of args, pal.\n"));
		//ERROR HANDLING
		exit(EXIT_FAILURE);
	}
	return ;
}

//returns the index position of the last set bit of a number
int	bit_i(int bin)
{
	int i;

	i = 0;
	while (bin >> i)
		i++;
	return(i);
}
