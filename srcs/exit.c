/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cpieri <cpieri@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/23 09:05:16 by cpieri            #+#    #+#             */
/*   Updated: 2018/06/28 09:59:10 by cvautrai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"
#include <stdlib.h>

void	quit_exe(t_all param)
{
	SDL_DestroyRenderer(param.env->rend);
	SDL_DestroyWindow(param.env->win);
	IMG_Quit();
	TTF_Quit();
	SDL_Quit();
	free_ui(&param);
	free(param.env);
	exit(0);
}
