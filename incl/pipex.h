/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iyahoui- <iyahoui-@student.42quebec.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/27 22:46:09 by iyahoui-          #+#    #+#             */
/*   Updated: 2022/02/09 12:57:28 by iyahoui-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# include "../libft/libft.h"
# include <stdlib.h>
# include <unistd.h>
# include <errno.h>
# include <fcntl.h>
# include <sys/wait.h>

//DEFINES
# define HEREDOC	"here_doc"
# define _ARGC_MIN	5

//TYPEDEFS
typedef int			t_access;
typedef int			t_error;

//STRUCTS
typedef struct s_file
{
	char		*filepath;
	t_access	access_flags;
}	t_file;

typedef struct s_cmd
{
	char		**cmd_argv;
	int			in_fd;	
	int			out_fd;	
	t_access	access_flags;
	t_error		cmd_stat;
}	t_cmd;

typedef struct s_main_container
{
	t_cmd	*first_cmd;
	t_file	*in_file;
	t_file	*out_file;
	char	**pathv;
	int		nb_cmds;
}	t_main_cont;

//ENUMS
typedef enum s_fflags
{
	F_EXISTS	= 1 << 0,
	F_CANREAD	= 1 << 1,
	F_CANWRITE	= 1 << 2,
	F_CANEXEC	= 1 << 3
}	t_fflags;

typedef enum s_errflags
{
	E_MALLOC	= 1 << 0,
	E_SPLIT		= 1 << 1,
	E_PIPE		= 1 << 2,
	E_ENVPATH	= 1 << 3,
	E_NOCMD		= 1 << 4,
	E_NOEXEC	= 1 << 5
}	t_errflags;

//UTILS
//Ultimately to be moved to libft submodule
char	*get_env_var(char *const *envp, char *var_name);
void	ft_print_split(char **split_arr, char *name);
void	ft_strcat_iter(char **vector, char *to_cat);
char	*ft_get_last_token(char *string, char delimiter);
char	*ft_strjoin_n(size_t nb_strings, ...);	//NEEDS STDARG LIB

//Pipex-specific:
void	check_args(int argc, char **argv);
t_error	get_file_mode(char *filepath);

//INIT
t_error	init(t_main_cont *container, int argc);
t_error	init_container(t_main_cont *container, int nb_cmds);
t_error	init_cmds(t_cmd *first_cmd, size_t nb_cmds);

//PARSING
t_error	parse(t_main_cont *container, int argc, char **argv, char *const *envp);
t_error	parse_pathv(char ***pathv, char *const *envp);
t_error	parse_file(t_file *file_struct, char *filepath);
t_error	parse_cmds(t_main_cont *cont, char **argv);
t_error	find_cmd(t_cmd *cmd_i, char **pathv);

//REDIRECTIONS
void	redirect_in_file(t_main_cont *cont);
void	redirect_out_file(t_main_cont *cont);
void	redirect(t_main_cont *cont);

//EXECUTION
int		execute(t_main_cont *cont, char *const *envp);

//ERROR HANDLING
void	pipex_error(t_error err);
void	file_error(t_file *file);
void	cmd_error(t_cmd *cmd_i);

//CLEANUP
void	cleanup(t_main_cont *container);

//BONUS
t_error	heredoc(t_main_cont *cont, int argc, char *delimiter);

//TO REMOVE
void	parse_test(t_main_cont *cont);
//END OF REMOVE

#endif