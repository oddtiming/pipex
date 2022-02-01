/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iyahoui- <iyahoui-@student.42quebec.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/27 22:46:09 by iyahoui-          #+#    #+#             */
/*   Updated: 2022/01/31 20:11:38 by iyahoui-         ###   ########.fr       */
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
//END OF REMOVE

//DEFINES
# define _ARGC_MIN 5
# define E_MALLOC	1 << 0
# define E_ENVPATH	1 << 1
# define E_SPLIT	1 << 2
# define E_PIPE		1 << 3
# define E_ACCESS	1 << 4

// bitfield (int = 32)
// 	typedef union{
	// is_set : 1
	// }
// 	E_MALLOC : 1; 
// 	E_ENVPATH
// 	E_SPLIT
// 	E_PIPE
// 	E_ACCESS
// 	//Function
// 	E_PARSECMD
// 	E_PARSEPATH	
// 	//Parameter
// 	//this would be t_err
//
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
	t_access	access_flags;	//Needs to be freed
}	t_cmd;

typedef struct s_main_container
{
	//Should commands be stored as a single pointer or a 2D array?
	//pointer	-->	harder arithmetic, less chances of deprecating
	//array		-->	more intuitive, but more leak-prone
	t_cmd	*first_cmd;	//Who the fuck knows what it needs
	t_file	*in_file;	//Needs to be freed
	t_file	*out_file;	//Needs to be freed
	char	**pathv;	//Needs to be ft_split_freed
	size_t	nb_cmds;	//simply assign it a value
}	t_main_cont;

// TO REMOVE
typedef struct s_args
{
	char	*in_file;
	char	*out_file;
	char	**pathv;
	char	**envp_ptr;
	char	***cmds;
	int		cmds_count;
}	t_args;
// END OF REMOVE

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
t_error	init(t_main_cont *container, char **argv, int argc);
t_error	init_container(t_main_cont *container, int nb_cmds);
t_error	init_cmds(t_cmd *first_cmd, char **argv, size_t nb_cmds);

//PARSING
t_error	parse(t_main_cont *container, int argc, char **argv, char *const *envp);
t_error	parse_pathv(char ***pathv, char *const *envp);
t_error	parse_file(t_file *file_struct, char *filepath);
void	find_cmd(t_cmd *cmd_i, char **pathv);

//REDIRECTIONS

//EXECUTION
t_error	execute(t_cmd *first_cmd, char *const *envp);

//ERROR HANDLING
void	exit_on_err(t_error stat);
void	print_err_msg(t_error stat);

//CLEANUP
t_error	cleanup(t_main_cont *container);

//TEST FUNCTIONS -- TO REMOVE
void	access_test(t_args *args);
void	parse_test(t_args *args);
//END OF REMOVE

#endif