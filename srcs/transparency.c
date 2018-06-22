/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   transparency.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmilon <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/21 10:22:20 by tmilon            #+#    #+#             */
/*   Updated: 2018/06/22 16:44:41 by tmilon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

int	transparency(t_all *param, t_ray ray, int fastmode)
{
	int			trans_color;
	t_intersect	intersection;

	trans_color = 0;
	if ((get_nearest_intersection(&ray, param->scene, &intersection, DIST_MAX)))
	{
		if (fastmode == 1)
			return (intersection.shape_copy.color);
		trans_color = set_color(param, intersection);
		if (intersection.shape_copy.opacity != 1)
		{
			ray.origin = vector_op(ray.origin, vector_op(ray.direction,
					new_vector_3d_unicoord(ray.maxdist), '*'), '+');
			trans_color = interpolate(transparency(param, ray, fastmode),
					trans_color, intersection.shape_copy.opacity);
		}
	}
	return (trans_color);
}

int	shadow_transp(t_all *param, t_ray ray, int start_color)
{
	int			shad_color;
	int			next_point;
	double		actual_dist;
	t_intersect	inter;

	shad_color = -1;
	actual_dist = ray.maxdist;
	if (get_nearest_intersection(&ray, param->scene, &inter, ray.maxdist))
	{
		if (inter.shape_copy.opacity == 1.0)
			shad_color = 0;
		else
		{
			shad_color = interpolate(inter.shape_copy.color, 0,
							inter.shape_copy.opacity);
			shad_color = interpolate(start_color, shad_color,
							inter.shape_copy.opacity);
			ray.origin = vector_op(ray.origin, vector_op(ray.direction,
							new_vector_3d_unicoord(ray.maxdist), '*'), '+');
			actual_dist -= ray.maxdist;
			ray.previous_inter_id = inter.shape_copy.id;
			ray.maxdist = actual_dist;
			next_point = shadow_transp(param, ray, shad_color);
			shad_color = next_point == -1 ? shad_color : next_point;
		}
	}
	return (shad_color);
}
