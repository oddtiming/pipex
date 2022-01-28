/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iyahoui- <iyahoui-@student.42quebec.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/27 23:21:25 by iyahoui-          #+#    #+#             */
/*   Updated: 2022/01/28 01:04:43 by iyahoui-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incl/pipex.h"

#define errv {
	"oof, that's on the malloc!",
	"have you lost your $PATH?",
	"that split ain't shit",
	"Le groupe Qualinet pour un travail sans retouches!",
	NULL
}

void	exit_on_err(t_status stat)
{
	if (!stat)
		return ;

	(void)(stat & E_MALLOC) && strerror(errv[bctod(E_MALLOC)]);
}

void	print_err_msg(t_status stat)
{
	(void) (stat & E_MALLOC) strerror(errv[bctod(E_MALLOC)]));
}
