/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iyahoui- <iyahoui-@student.42quebec.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/27 22:46:09 by iyahoui-          #+#    #+#             */
/*   Updated: 2022/01/28 01:02:43 by iyahoui-         ###   ########.fr       */
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
# define E_ACCFAIL	1 << 4

// bitfield (int = 32)
// 	//Type
// 	E_MALLOC : 1; 
// 	E_ENVPATH
// 	E_SPLIT
// 	E_PIPE
// 	E_ACCFAIL
	
// 	//Function
// 	E_PARSECMD
// 	E_PARSEPATH	
	
// 	//Parameter
// 	//this would be t_err
//
//TYPEDEFS
typedef uint_fast8_t	t_access;
typedef uint8_t			t_status;
//NOT SURE: I'm uncertain as to whether a uint8_t would be better

//STRUCTS
typedef struct s_file
{
	char		*filepath;
	t_access	access_flags;
}	t_file;

typedef struct s_cmd
{
	// char *const	*envp;
	char		**cmd_argv;
	t_file		cmd_filepath;
	int			in_fd;
	int			out_fd;
	size_t		cmd_index;
}	t_cmd;

typedef struct s_main_container
{
	t_file	*in_file;	//Needs to be freed
	t_file	*out_file;	//Needs to be freed
	char	**pathv;	//Needs to be ft_split_freed
	//Should commands be stored as a single pointer or a 2D array?
	//pointer	-->	harder arithmetic, less chances of deprecating
	//array		-->	more intuitive, but more leak-prone
	t_cmd	*first_cmd;		//Who the fuck knows what it needs
	size_t	nb_cmds;	//simply give it a value
}	t_main_container;

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
void	argc_check(int argc);

//PARSING
t_status	parse_args(t_main_container *container, int argc, char **argv, char *const *envp);
t_status	parse_pathv(char ***pathv, char *const *envp);
t_status	parse_cmds(t_cmd *first_cmd, char **argv, size_t nb_cmds);
t_status	init_container(t_main_container *container);
t_status	init_file(t_file *file_struct, char *filepath);

//REDIRECTIONS

//EXECUTION
t_status	execute_cmds(t_cmd *first_cmd, char *const *envp);

//ERROR HANDLING
void	exit_on_err(t_status stat);
void	print_err_msg(t_status stat);

//CLEANUP
t_status	cleanup(t_main_container *container);

//TEST FUNCTIONS -- TO REMOVE
void	access_test(t_args *args);
void	parse_test(t_args *args);
//END OF REMOVE

#endif