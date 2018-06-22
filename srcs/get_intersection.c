/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_intersection.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cvautrai <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/21 16:02:53 by tmilon            #+#    #+#             */
/*   Updated: 2018/06/22 11:31:24 by cvautrai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"
#include <stdlib.h>

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
			ray->maxdist = maxdist;
			nearest_shape = shape;
		}
		scene.shape_lst = scene.shape_lst->next;
	}
	if (nearest_shape.color != -1)
		*nearest_intersect = new_intersection(nearest_shape,
				adapt_ray(*ray, nearest_shape.inv_rot), maxdist);
	return (nearest_shape.color != -1 ? maxdist : 0);
}
