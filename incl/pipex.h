/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iyahoui- <iyahoui-@student.42quebec.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/27 22:46:09 by iyahoui-          #+#    #+#             */
/*   Updated: 2022/02/06 21:14:31 by iyahoui-         ###   ########.fr       */
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
//TO REMOVE
# include <stdio.h>
# include <string.h>
//END OF REMOVE

//DEFINES
# define HEREDOC	"here_doc"
# define _ARGC_MIN	5
# define E_MALLOC	1 << 0
# define E_ENVPATH	1 << 1
# define E_SPLIT	1 << 2
# define E_PIPE		1 << 3
# define E_ACCESS	1 << 4

//TYPEDEFS
typedef uint_fast8_t	t_uf8;
typedef t_uf8			t_access;
typedef t_uf8			t_error;



//STRUCTS
typedef struct s_file
{
	char		*filepath;
	t_access	access_flags;
}	t_file;

typedef struct s_cmd
{
	// char *const	*envp;
	char		**cmd_argv;		//Needs to be ft_split_freed
	int			in_fd;	
	int			out_fd;	
	t_access	access_flags;
	t_error		cmd_stat;
}	t_cmd;

typedef struct s_main_container
{
	t_cmd	*first_cmd;	//argvs need to be freed. Only first_cmd needs to be freed
	t_file	*in_file;	//Needs to be freed
	t_file	*out_file;	//Needs to be freed
	char	**pathv;	//Needs to be ft_split_freed
	size_t	nb_cmds;	//simply assign it a value
}	t_main_cont;


//ENUMS
typedef enum	s_fflags
{
	F_EXISTS	= 1 << 0,
	F_CANREAD	= 1 << 1,
	F_CANWRITE	= 1 << 2,
	F_CANEXEC	= 1 << 3
}	t_fflags;


//UTILS
//Ultimately to be moved to libft submodule
char	*get_env_var(char *const *envp, char *var_name);
void	ft_print_split(char **split_arr, char *name);
void	ft_strcat_iter(char **vector, char *to_cat);
char	*ft_get_last_token(char *string, char delimiter);
char	*ft_strjoin_n(size_t nb_strings, ...);	//NEEDS STDARG LIB

//Pipex-specific:
void	check_argc(int argc);
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
t_error	redirect_in_file(t_main_cont *cont);
t_error	redirect_out_file(t_main_cont *cont);
t_error	redirect(t_main_cont *cont);

//EXECUTION
void	execute(t_main_cont *cont, char *const *envp);

//ERROR HANDLING
void	exit_on_err(t_error stat);
void	print_err_msg(t_error stat);

//CLEANUP
void	cleanup(t_main_cont *container);

//BONUS
void	read_heredoc(char *delimiter);

//TO REMOVE
void	parse_test(t_main_cont *cont);
//END OF REMOVE

#endif