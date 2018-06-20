/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   display.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cpieri <cpieri@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/21 16:02:53 by tmilon            #+#    #+#             */
/*   Updated: 2018/06/20 09:47:24 by cvautrai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"
#include <stdlib.h>
#include <math.h>
#include <pthread.h>

t_vector3d	bump_mapping(t_vector3d normal, int colorint)
{
	double	mult;
	t_color	color;

	color = int_to_color(colorint);
	mult = color.b / 255.0
		+ color.r / 255.0
		+ color.g / 255.0;
	mult /= 3.0;
	return (vector_op(normal, new_vector_3d_unicoord(mult), '*'));
}

t_intersect	new_intersection(t_shape shape, t_ray ray, double point_dist)
{
	t_vector3d	tmp;
	t_intersect	ret;
	t_vector3d	(*normals[10])(t_shape shape, t_vector3d inter);

	normals[SPHERE] = &sphere_normal;
	normals[PLANE] = &plane_normal;
	normals[CYLINDER] = &cylinder_normal;
	normals[CONE] = &cone_normal;
	normals[TORUS] = &torus_normal;
	shape.origin = adjust_direction(shape.origin, shape.inv_rot);
	ret.point = vector_op(ray.origin, shape.origin, '-');
	tmp = vector_op(ray.direction, new_vector_3d_unicoord(point_dist), '*');
	ret.point = vector_op(ret.point, tmp, '+');
	ret.normal = normalize(normals[shape.type](shape, ret.point));
	if (shape.type == PLANE)
		if (dotprod(ray.direction, ret.normal) > DIST_MIN)
			ret.normal = vector_op(ret.normal, new_vector_3d_unicoord(-1), '*');
	shape = texture(&ret, shape);
	ret.shape_copy = shape;
	if (shape.textunit.has_texture)
		ret.normal = bump_mapping(ret.normal, shape.color);
	ret.point = vector_op(ret.point, shape.origin, '+');
	ret.point = adjust_direction(ret.point, shape.rot);
	ret.normal = adjust_direction(ret.normal, shape.rot);
	ret.dir_to_cam = adjust_direction(ray.direction, shape.rot);
	return (ret);
}

double		get_nearest_intersection(t_ray *ray, t_scene scene,
		t_intersect *nearest_intersect, double maxdist)
{
	int			(*collisions[10])(t_shape shape, t_ray ray, double *t);
	t_shape		shape;
	t_shape		nearest_shape;

	collisions[SPHERE] = &intersect_sphere;
	collisions[PLANE] = &intersect_plane;
	collisions[CYLINDER] = &intersect_cylinder;
	collisions[CONE] = &intersect_cone;
	collisions[TORUS] = &intersect_torus;
	nearest_shape.color = 0;
	while (scene.shape_lst != NULL)
	{
		shape = *(t_shape*)scene.shape_lst->content;
		if (shape.type == -1)
			break ;
		if (ray->previous_inter_id != shape.id && collisions[shape.type](shape,
					adapt_ray(*ray, shape.inv_rot), &maxdist))
			nearest_shape = shape;
		scene.shape_lst = scene.shape_lst->next;
	}
	if (nearest_shape.color)
	{
		*nearest_intersect = new_intersection(nearest_shape,
				adapt_ray(*ray, nearest_shape.inv_rot), maxdist);
		ray->origin = vector_op(ray->origin, vector_op(ray->direction,
					new_vector_3d_unicoord(maxdist), '*'), '+');
	}
	return (nearest_shape.color ? maxdist : 0);
}

int			transparency(t_scene scene, t_ray ray, t_intersect intersection,
		t_point p, t_data data)
{
	if (get_nearest_intersection(&ray, scene, &intersection, DIST_MAX))
	{
		//rename set_light
		p.color = set_color(scene, intersection, data);
		if (intersection.shape_copy.opacity != 1)
		{
			ray.previous_inter_id = intersection.shape_copy.id;
			p.color = interpolate(transparency(scene, ray, intersection, p, data),
					p.color, intersection.shape_copy.opacity);
		}
		return (p.color);
	}
	return (0); //noir
}

static void	raytrace(t_all *param, t_point p)
{
	t_ray		ray;
	t_vector3d	direction;
	t_intersect	intersection;

	direction = set_axe(p.x, p.y, &(param->scene.camera), param->env->surf);
	ray = new_ray(param->scene.camera.origin, direction);
	if (get_nearest_intersection(&ray, param->scene, &intersection, DIST_MAX))
	{
		//rename set_light
		p.color = set_color(param->scene, intersection, param->data);
		if (intersection.shape_copy.opacity != 1)
			p.color = interpolate(transparency(param->scene, ray, intersection, p,
						param->data), p.color, intersection.shape_copy.opacity);
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
//	printf("surf: %i x %i...\n", param.env->surf->w, param.env->surf->h);
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
	i--;
	while (i >= 0)
	{
		pthread_join(thread_id[i], NULL);
		i--;
	}
	p = new_point (-1, -1, 0);
	while (++p.y < param.env->surf->h)
	{
		p.x = -1;
		while (++p.x < param.env->surf->w)
		{
			p.color = param.colorarray[p.x + p.y * param.env->surf->w];
			img_put_pixel(param.env->surf, p);
		}
	}
	SDL_BlitSurface(param.env->surf, NULL, param.env->s_filter, NULL);
	free(param.colorarray);
}
