/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   display.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cpieri <cpieri@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/21 16:02:53 by tmilon            #+#    #+#             */
/*   Updated: 2018/06/06 10:45:45 by tmilon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"
#include <stdlib.h>
#include <math.h>

t_intersect	new_intersection(t_shape shape, t_ray ray, double point_dist)
{
	t_vector3d	tmp;
	t_intersect	ret;
	t_vector3d	(*normals[10])(t_shape shape, t_vector3d inter);

	normals[SPHERE] = &sphere_normal;
	normals[PLANE] = &plane_normal;
	normals[CYLINDER] = &cylinder_normal;
	normals[CONE] = &cone_normal;
	shape.origin = adjust_direction(shape.origin, shape.inv_rot);
	ret.point = vector_op(ray.origin, shape.origin, '-');
	tmp = vector_op(ray.direction, new_vector_3d_unicoord(point_dist), '*');
	ret.point = vector_op(ret.point, tmp, '+');
	ret.normal = normalize(normals[shape.type](shape, ret.point));
	shape.color = texture(shape.color, ret, shape);
	ret.shape_copy = shape;
	if (shape.type == PLANE)
	{
		if (dotprod(ray.direction, ret.normal) > DIST_MIN)
			ret.normal = vector_op(ret.normal, new_vector_3d_unicoord(-1), '*');
	}
	ret.point = vector_op(ret.point, shape.origin, '+');
	ret.point = adjust_direction(ret.point, shape.rot);
	ret.normal = adjust_direction(ret.normal, shape.rot);
	ret.normal = normalize(ret.normal);
	ret.dir_to_cam = adjust_direction(ray.direction, shape.rot);
	return (ret);
}

int			get_nearest_intersection(t_ray ray, t_list *shape_lst,
		t_intersect *nearest_intersect, double maxdist)
{
	int			(*collisions[10])(t_shape shape, t_ray ray, double *t);
	t_shape		shape;
	t_shape		nearest_shape;

	collisions[SPHERE] = &intersect_sphere;
	collisions[PLANE] = &intersect_plane;
	collisions[CYLINDER] = &intersect_cylinder;
	collisions[CONE] = &intersect_cone;
	nearest_shape.color = 0;
	while (shape_lst != NULL)
	{
		shape = *(t_shape*)shape_lst->content;
		if (shape.type == -1)
			break ;
		if (collisions[shape.type](shape,
					adapt_ray(ray, shape.inv_rot), &maxdist))
			nearest_shape = shape;
		shape_lst = shape_lst->next;
	}
	if (nearest_shape.color)
		*nearest_intersect = new_intersection(nearest_shape,
				adapt_ray(ray, nearest_shape.inv_rot), maxdist);
	return (nearest_shape.color ? 1 : 0);
}

void		raytrace(t_scene scene, t_env *env, t_point p, t_data data)
{
	t_ray		ray;
	t_vector3d	direction;
	t_intersect	intersection;

	direction = set_axe(p.x, p.y, &(scene.camera));
	ray = new_ray(scene.camera.origin, normalize(direction));
	if (get_nearest_intersection(ray, scene.shape_lst, &intersection, DIST_MAX))
	{
		p.color = set_color(scene.light_lst, scene.shape_lst, intersection, data);
		img_put_pixel(env->surf, p);
	}
}

void		setup_multithread(t_scene scene, t_env *env, t_data data)
{
	t_point	p;

	p = new_point(-1, -1, 0);
	while (++p.y < I_HEIGHT)
	{
		p.x = -1;
		if ((int)p.y % 5 == 0 || data.fastmode == -1)
			while (++p.x < I_WIDTH)
				if ((int)p.x % 5 == 0 || data.fastmode == -1)
					raytrace(scene, env, p, data);
	}
	SDL_BlitSurface(env->surf, NULL, env->s_filter, NULL);
}
