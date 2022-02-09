/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iyahoui- <iyahoui-@student.42quebec.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/27 22:46:00 by iyahoui-          #+#    #+#             */
/*   Updated: 2022/02/08 20:09:13 by iyahoui-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

t_error	parse(t_main_cont *container, int argc, char **argv, char *const *envp)
{
	t_error	parse_status;

	parse_status = 0;
	parse_status |= parse_file(container->in_file, argv[1]);
	if (parse_status & E_MALLOC)
		return (E_MALLOC);
	parse_status |= parse_file(container->out_file, argv[argc - 1]);
	if (parse_status & E_MALLOC)
		return (E_MALLOC);
	parse_status |= parse_pathv(&container->pathv, envp);
	if (parse_status & (E_MALLOC | E_SPLIT))
		return (parse_status);
	if (!ft_strncmp(container->in_file->filepath, HEREDOC, sizeof(HEREDOC)))
		parse_status |= parse_cmds(container, argv + 1);
	else
		parse_status |= parse_cmds(container, argv);
	if (parse_status & (E_MALLOC | E_SPLIT))
		return (parse_status);
	return (parse_status);
}

t_error	parse_cmds(t_main_cont *cont, char **argv)
{
	t_cmd	*cmd_i;
	int		i;
	int		status;

	i = 0;
	while (i < cont->nb_cmds)
	{
		cmd_i = (cont->first_cmd) + i;
		cmd_i->cmd_argv = ft_split(argv[2 + i], ' ');
		if (!(cmd_i->cmd_argv[0]))
			return (E_SPLIT);
		status = find_cmd(cmd_i, cont->pathv);
		if (status == E_MALLOC)
			return (E_MALLOC);
		if (cmd_i->access_flags == 0)
			cmd_i->cmd_stat = E_NOCMD;
		else if (!(cmd_i->access_flags & F_CANEXEC))
			cmd_i->cmd_stat = E_NOEXEC;
		i++;
	}
	return (cmd_i->cmd_stat);
}

t_error	parse_pathv(char ***pathv, char *const *envp)
{
	char	*envp_path;

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

/**
 * @param file_struct	needs to have been previously malloced
 * @param filepath 		does not need to be malloced
 * @return t_error 
 * 		E_MALLOC if ft_strdup() fails
 * 		E_ACCESS if file does not exist
 */
t_error	parse_file(t_file *file_struct, char *filepath)
{
	file_struct->filepath = ft_strdup(filepath);
	if (!file_struct->filepath)
		return (E_MALLOC);
	file_struct->access_flags = get_file_mode(filepath);
	return (0);
}

t_error	find_cmd(t_cmd *cmd_i, char **pathv)
{
	int		i;
	char	*temp_path;

	if (!pathv || is_set(cmd_i->cmd_argv[0][0], ".~/"))
	{
		cmd_i->access_flags = get_file_mode(cmd_i->cmd_argv[0]);
		return (0);
	}
	i = 0;
	while (pathv[i])
	{
		temp_path = ft_strjoin(pathv[i], cmd_i->cmd_argv[0]);
		if (!temp_path)
			return (E_MALLOC);
		cmd_i->access_flags = get_file_mode(temp_path);
		if (cmd_i->access_flags)
		{
			free (cmd_i->cmd_argv[0]);
			cmd_i->cmd_argv[0] = temp_path;
			return (0);
		}
		free(temp_path);
		i++;
	}
	return (0);
}
