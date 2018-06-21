/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   display.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cpieri <cpieri@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/21 16:02:53 by tmilon            #+#    #+#             */
/*   Updated: 2018/06/21 10:35:08 by tmilon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"
#include <stdlib.h>
#include <pthread.h>

t_intersect	new_intersection(t_shape shape, t_ray ray, double point_dist)
{
	t_vector3d	tmp;
	t_intersect	ret;

	shape.origin = adjust_direction(shape.origin, shape.inv_rot);
	ret.point = vector_op(ray.origin, shape.origin, '-');
	tmp = vector_op(ray.direction, new_vector_3d_unicoord(point_dist), '*');
	ret.point = vector_op(ret.point, tmp, '+');
	ret.normal = normals(shape, ret.point);
	if (shape.type == PLANE)
		if (dotprod(ray.direction, ret.normal) > DIST_MIN)
			ret.normal = vector_op(ret.normal, new_vector_3d_unicoord(-1), '*');
	ret.normal = vector_op(ret.normal,
			new_vector_3d_unicoord(ray.normal_dir), '*');
	shape = texture(&ret, shape, ray.normal_dir);
	if (shape.textunit.has_texture)
		ret.normal = bump_mapping(ret.normal, shape.color);
	ret.shape_copy = shape;
	ret.point = vector_op(ret.point, shape.origin, '+');
	ret.point = adjust_direction(ret.point, shape.rot);
	ret.normal = adjust_direction(ret.normal, shape.rot);
	ret.dir_to_cam = adjust_direction(ray.direction, shape.rot);
	return (ret);
}

double		get_nearest_intersection(t_ray *ray, t_scene scene,
		t_intersect *nearest_intersect, double maxdist)
{
	t_shape		shape;
	t_shape		nearest_shape;
	int			tmp;

	nearest_shape.color = -1;
	while (scene.shape_lst != NULL)
	{
		shape = *(t_shape*)scene.shape_lst->content;
		if (shape.type == -1)
			break ;
		if (ray->previous_inter_id != shape.id && (tmp = collisions(shape,
					adapt_ray(*ray, shape.inv_rot), &maxdist)))
		{
			ray->normal_dir = tmp;
			nearest_shape = shape;
		}
		scene.shape_lst = scene.shape_lst->next;
	}
	if (nearest_shape.color != -1)
		*nearest_intersect = new_intersection(nearest_shape,
				adapt_ray(*ray, nearest_shape.inv_rot), maxdist);
	return (nearest_shape.color != -1 ? maxdist : 0);
}

static void	raytrace(t_all *param, t_point p)
{
	t_ray		ray;
	t_vector3d	direction;
	t_intersect	intersection;
	double		maxdist;

	direction = set_axe(p.x, p.y, &(param->scene.camera), param->env->surf);
	ray = new_ray(param->scene.camera.origin, direction);
	if ((maxdist = get_nearest_intersection(&ray, param->scene, &intersection,
					DIST_MAX)))
	{
		ray.origin = vector_op(ray.origin, vector_op(ray.direction,
					new_vector_3d_unicoord(maxdist), '*'), '+');
		if (param->data.fastmode == 1)
			p.color = intersection.shape_copy.color;
		else
		{
			p.color = set_color(param, intersection);
			if (intersection.shape_copy.opacity != 1)
				p.color = interpolate(transparency(param, ray, intersection),
					p.color, intersection.shape_copy.opacity);
		}
		param->colorarray[p.x + p.y * param->env->surf->w] = p.color;
	}
}

static void	*raytrace_thread(void *voidparam)
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

void		setup_multithread(t_all param)
{
	t_point		p;
	t_all		tparam[THREAD_LIMIT];
	pthread_t	thread_id[THREAD_LIMIT];
	int			i;

	i = 0;
	p = new_point(-1, -1, 0);
	param.colorarray = ft_memalloc((param.env->surf->w * param.env->surf->h)
			* sizeof(int));
	while (++p.y < param.env->surf->h)
	{
		if (p.y % (param.env->surf->h / THREAD_LIMIT) == 0 && i < THREAD_LIMIT)
		{
			ft_memcpy((void*)&tparam[i], (void*)&param, sizeof(t_all));
			tparam[i].point = p;
			tparam[i].maxy = p.y + (param.env->surf->h / THREAD_LIMIT);
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
