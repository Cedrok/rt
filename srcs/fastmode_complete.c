/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fastmode_complete.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Pringles <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/20 12:01:37 by Pringles          #+#    #+#             */
/*   Updated: 2018/06/21 10:36:03 by tmilon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"
#include <stdlib.h>
#include <math.h>
#include <pthread.h>

static void	color_closest_point(t_all *param, t_point p)
{
	if (p.x < 3 && p.y < 3)
		param->colorarray[p.x + p.y * param->env->surf->w] =
			param->colorarray[p.x - (p.x % 5) + (p.y - p.y % 5)
			* param->env->surf->w];
	else if (p.x >= 3 && p.y < 3)
		param->colorarray[p.x + p.y * param->env->surf->w] =
			param->colorarray[
			(int)fmin(p.x + 5 - (p.x % 5), param->env->surf->w - 1)
			+ (p.y - p.y % 5)
			* param->env->surf->w];
	else if (p.x >= 3 && p.y >= 3)
		param->colorarray[p.x + p.y * param->env->surf->w] =
			param->colorarray[
			(int)fmin(p.x + 5 - (p.x % 5), param->env->surf->w - 1)
			+ (int)fmin((p.y + 5 - p.y % 5), param->maxy - 1)
			* param->env->surf->w];
	else if (p.x < 3 && p.y >= 3)
		param->colorarray[p.x + p.y * param->env->surf->w] =
			param->colorarray[
			p.x - (p.x % 5) + (int)fmin(p.y + 5 - p.y % 5, param->maxy - 1)
			* param->env->surf->w];
}

void		fastmode_complete(t_all *param)
{
	t_point	p;

	p = param->point;
	while (p.y < param->maxy)
	{
		p.x = -1;
		if (p.y % 5 != 0)
			while (++p.x < param->env->surf->w)
				if (p.x % 5 != 0)
					color_closest_point(param, p);
		p.y++;
	}
}
