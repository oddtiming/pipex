/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iyahoui- <iyahoui-@student.42quebec.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/08 20:19:25 by iyahoui-          #+#    #+#             */
/*   Updated: 2022/02/08 20:20:49 by iyahoui-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

//This fct needs reviewing, I do not like how it handles memory 
//allocation and its potential failure. See Notion page for more details.
char	*get_env_var(char *const *envp, char *var_name)
{
	int		var_strlen;
	int		envp_strlen;
	int		i;
	char	*var_val;

	i = 0;
	if (!var_name || !envp)
		return (NULL);
	var_strlen = ft_strlen(var_name);
	while (envp[i])
	{
		if (!ft_strncmp(envp[i], var_name, var_strlen))
		{
			envp_strlen = ft_strlen(envp[i]);
			var_val = malloc(envp_strlen - var_strlen);
			var_val = ft_strncpy(var_val, (char *)envp[i] + var_strlen + 1, \
				envp_strlen - var_strlen);
			return (var_val);
		}
		i++;
	}
	return (NULL);
}

void	check_args(int argc, char **argv)
{
	if (argc < _ARGC_MIN || \
			(!ft_strncmp(argv[1], "here_doc", sizeof("here_doc")) && \
			argc < _ARGC_MIN + 1))
	{
		write(2, "pipex: Imma need at least 4 args\n", \
			sizeof("pipex: Imma need at least 4 args\n"));
		exit(EXIT_FAILURE);
	}
	return ;
}

t_access	get_file_mode(char *filepath)
{
	t_access	access_status;

	access_status = 0;
	access_status |= (!access(filepath, F_OK)) << 0;
	if (!access_status)
		return (0);
	access_status |= (!access(filepath, R_OK)) << 1;
	access_status |= (!access(filepath, W_OK)) << 2;
	access_status |= (!access(filepath, X_OK)) << 3;
	return (access_status);
}
