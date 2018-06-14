/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cpieri <cpieri@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/23 09:05:16 by cpieri            #+#    #+#             */
/*   Updated: 2018/06/14 10:00:27 by cvautrai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"
#include <stdlib.h>

void	parsing_quit(char *msg, char **splt_ln, char *ln)
{
	ft_putendl(msg);
	free_multiarray(splt_ln);
	free(ln);
	exit(-1);
}

void	quit_exe(t_all param)
{
	SDL_DestroyRenderer(param.env->rend);
	SDL_DestroyWindow(param.env->win);
	IMG_Quit();
	TTF_Quit();
	SDL_Quit();
	free(param.env);
	exit(0);
}
