/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iyahoui- <iyahoui-@student.42quebec.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/27 23:21:25 by iyahoui-          #+#    #+#             */
/*   Updated: 2022/02/08 16:39:31 by iyahoui-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incl/pipex.h"

// #ifndef MALLOC_ERR
// # error "of, that's on the malloc!"
// #endif

// #ifndef PATH_ERR
// # error "have you lost your $PATH?"
// #endif

// #ifndef SPLIT_ERR
// # error "that split ain't shit"
// #endif

// #ifndef PIPE_ERR
// # error "Ceci n'est pas une pipe"
// #endif

// #define errv {
// 	"oof, that's on the malloc!",
// 	"have you lost your $PATH?",
// 	"that split ain't shit",
// 	"Le groupe Qualinet pour un travail sans retouches!",
// 	NULL
// }

typedef struct s_errstruct
{
	union
	{
		int	e_malloc : 1;
		int	e_envpath : 1;
		int	e_split : 1;
		int	e_pipe : 1;
		int	e_access : 1;
	};
	int	all;
} t_errstruct;

// void	exit_on_err(t_error stat)
// {
// 	if (!stat)
// 		return ;

// 	(void)(stat & E_MALLOC) && strerror(errv[bctod(E_MALLOC)]);
// }

// void	print_err_msg(t_error stat)
// {
// 	t_error	err;
// 	int	*err_ptr;

// 	err_ptr = (int *)(&err);
// 	err_ptr.t_errtype.e_malloc = 1;
// 	printf("err_ptr.t_errtype.e_malloc = %d\n", err_ptr.t_errtype.e_malloc)
// 	(void) (stat & E_MALLOC) strerror(errv[bctod(E_MALLOC)]));
// }
