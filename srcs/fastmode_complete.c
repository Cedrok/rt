/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fastmode_complete.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cpieri <cpieri@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/22 09:49:20 by Pringles          #+#    #+#             */
/*   Updated: 2018/06/24 15:25:07 by cpieri           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"
#include <stdlib.h>
#include <math.h>
#include <pthread.h>

void		btn_fastmode(void *p, int type)
{
	t_all	*param;

	param = (t_all*)p;
	(void)type;
	param->data.fastmode *= -1;
	refresh_img(param);
}

static void	color_closest_point(t_all *param, t_point p, int w)
{
	if (param->colorarray[p.x - (p.x % 5) + (p.y - p.y % 5) * w])
		param->colorarray[p.x + p.y * w] =
			param->colorarray[p.x - (p.x % 5) + (p.y - p.y % 5) * w];
	else if (param->colorarray[(int)fmin(p.x + 5 - (p.x % 5), w - 1)
			+ (p.y - p.y % 5) * w])
		param->colorarray[p.x + p.y * w] = param->colorarray[
			(int)fmin(p.x + 5 - (p.x % 5), w - 1) + (p.y - p.y % 5) * w];
	else if (param->colorarray[	(int)fmin(p.x + 5 - (p.x % 5), w - 1)
			+ (int)fmin((p.y + 5 - p.y % 5), param->maxy - 1) * w])
		param->colorarray[p.x + p.y * w] =
			param->colorarray[(int)fmin(p.x + 5 - (p.x % 5), w - 1)
			+ (int)fmin((p.y + 5 - p.y % 5), param->maxy - 1) * w];
	else
		param->colorarray[p.x + p.y * w] =
			param->colorarray[p.x - (p.x % 5) +
			(int)fmin(p.y + 5 - p.y % 5, param->maxy - 1) * w];
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
					color_closest_point(param, p, param->env->surf->w);
		p.y++;
	}
}
