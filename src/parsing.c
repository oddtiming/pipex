/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iyahoui- <iyahoui-@student.42quebec.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/27 22:46:00 by iyahoui-          #+#    #+#             */
/*   Updated: 2022/01/28 18:28:05 by iyahoui-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incl/pipex.h"


t_status	parse_args(t_main_container *container, int argc, char **argv, char *const *envp)
{
	t_status	stat_parse;

	container->nb_cmds = argc - 3;	//2 for files + 1 for argv[0]
	stat_parse = init_container(&container);
	if (stat_parse)
		return (stat_parse);

	stat_parse = init_file(container->in_file, argv[1]);
	if (stat_parse)
		return (stat_parse);
	
	stat_parse = init_file(container->out_file, argv[argc - 1]);
	if (stat_parse)
		return (stat_parse);
	
	stat_parse = parse_pathv(&(container->pathv), envp);
	if (stat_parse)
		return (stat_parse);

	//cmds has not been initialized at this point!
	stat_parse = parse_cmds(container->first_cmd, argv, container->nb_cmds);
	if (stat_parse)
		return (stat_parse);

	return (stat_parse);
}

t_status	parse_pathv(char ***pathv, char *const *envp)
{
	char		*envp_path;

	envp_path = get_env_var(envp, "PATH");
	if (!envp_path)
		return (E_ENVPATH);
	*pathv = ft_split(envp_path, ':');
	if (!*pathv)
		return (E_SPLIT);
	ft_strcat_iter(*pathv, "/");
	if (!*pathv)
		return (E_SPLIT);
	free(envp_path);
	return (0);
}


// This function is getting quite big, so it should probably be separated in two,
// one for init (piping, mallocing the embedded pointers) and one for parsing.
// For now I will simply add what I think is necessary for the parsing, but 
// the splitting of the function needs to be done, both for readability and size
t_status	parse_cmds(t_cmd *first_cmd, char **argv, size_t nb_cmds)
{
	t_cmd	*cmd_i;
	size_t	i;
	int		*pipe_fds;
	char	*temp_ptr;

	i = 0;
	//We need n - 1 pipes, b/c both ends of the line of cmds have I/O redir
	pipe_fds = malloc(2 * (nb_cmds - 1) * sizeof(int));
	while (i < nb_cmds)
	{
		cmd_i = first_cmd + i;
		cmd_i->cmd_index = i;
		
		//pipe() will not be called if !(first_condition)
		if ( i < (nb_cmds - 1) && pipe( pipe_fds + (2*i) ) );
			return(E_PIPE);

		cmd_i->cmd_argv = ft_split(argv[2 + i], ' ');
		if (!(cmd_i->cmd_argv[0]))
			return (E_SPLIT);

		cmd_i->cmd_filepath = malloc(sizeof(t_file));
		if (!cmd_i->cmd_filepath)
			return (E_MALLOC);

//Logic to assign the proper file to each command
//Since it will run with all the path, if the file exists, cmd_i->cmd_argv[0] will be replaced by temp_ptr.
//If the file is not executable, the error managet will display "/path/to/cmd: Permission denied"
//Otherwise, it will stay as the initial command string, and the error manager will display "cmd: not found in path"		
		for (int j = 0; pathv[j]; j++)
		{
			temp_ptr = cmd_i->cmd_argv[0];
			temp_ptr = strjoin(pathv[j], temp_ptr);
			//THIS LOGIC IS BROKEN, B/C init_file() USES strdup() ON t_file.filepath;
			if !(init_file(cmd_i->cmd_filepath, temp_ptr))
			{
				break ;
			}
			free(temp_ptr);
			
		}
		if (cmd_i->cmd_filepath->access_flags)
		{
			free (cmd_i->cmd_argv[0]);
			cmd_i->cmd_argv[0] = temp_ptr;
		}
		else
			init_file(cmd_i->cmd_filepath, cmd_i->cmd_argv[0]);
		//So if the parsing reaches this point, it means the file was not found in path, therefore it stays as is.

		//first_cmd has in_file's fd
		if (i > 0)
			cmd_i->in_fd = *(pipe_fds + 2*i);
		//last_cmd has out_file's fd
		if (i < nb_cmds - 1)
			cmd_i->out_fd = *(pipe_fds + 2*i + 1);
		i++;
	}
	free (pipe_fds);
	return (0);
}
