/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   display.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cpieri <cpieri@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/21 16:02:53 by tmilon            #+#    #+#             */
/*   Updated: 2018/06/28 09:06:38 by bspindle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"
#include <stdlib.h>
#include <pthread.h>

static void		raytrace(t_all *param, t_point p)
{
	t_ray		ray;
	t_vector3d	direction;

	direction = set_axe(p.x, p.y, &(param->scene.camera), param->env->surf);
	ray = new_ray(param->scene.camera.origin, direction);
	p.color = transparency(param, ray, param->data.fastmode);
	param->colorarray[p.x + p.y * param->env->surf->w] = p.color;
}

static void		*raytrace_thread(void *voidparam)
{
	t_all	*param;
	t_point	p;
	t_data	data;
	t_scene	env;

	param = (t_all*)voidparam;
	p = param->point;
	data = param->data;
	env = param->scene;
	while (p.y < param->maxy)
	{
		p.x = -1;
		if (p.y % 5 == 0 || data.fastmode == -1)
			while (++p.x < param->env->surf->w)
				if (p.x % 5 == 0 || data.fastmode == -1)
					raytrace(param, p);
		p.y++;
	}
	if (data.fastmode != -1)
		fastmode_complete(param);
	pthread_exit(0);
}

static t_all	set_tparam(t_all tparam, int i, t_point p, t_all param)
{
	ft_memcpy((void*)&tparam, (void*)&param, sizeof(t_all));
	tparam.point = p;
	tparam.maxy = (i < THREAD_LIMIT - 1 ? p.y + (param.env->surf->h
				/ THREAD_LIMIT) : param.env->surf->h);
	return (tparam);
}

void			setup_multithread(t_all param)
{
	t_point		p;
	t_all		tparam[THREAD_LIMIT];
	pthread_t	thread_id[THREAD_LIMIT];
	int			i;

	i = 0;
	p = new_point(-1, -1, 0);
	is_light_in(param.scene.light_lst, param.scene.shape_lst);
	if (!(param.colorarray = ft_memalloc((param.env->surf->w
				* param.env->surf->h) * sizeof(int))))
		ft_abort("Malloc failed in multithreads\n");
	while (++p.y < param.env->surf->h)
	{
		if (p.y % (param.env->surf->h / THREAD_LIMIT) == 0 && i < THREAD_LIMIT)
		{
			tparam[i] = set_tparam(tparam[i], i, p, param);
			pthread_create(&thread_id[i], NULL, raytrace_thread, &tparam[i]);
			i++;
		}
	}
	while (--i >= 0)
		pthread_join(thread_id[i], NULL);
	int_array_to_surf(param.env->surf, param.colorarray);
	SDL_BlitSurface(param.env->surf, NULL, param.env->s_filter, NULL);
	free(param.colorarray);
}
