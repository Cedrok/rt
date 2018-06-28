/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   transparency.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmilon <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/21 10:22:20 by tmilon            #+#    #+#             */
/*   Updated: 2018/06/28 09:07:17 by tmilon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

static t_shadunit	new_shadunit(t_ray *ray)
{
	t_shadunit	ret;

	ret.shad_color = -1;
	ret.actual_dist = ray->maxdist;
	ret.actual_id = ray->previous_inter_id;
	ray->previous_inter_id = -1;
	return (ret);
}

static void			update_ray_data(t_ray *ray, t_shadunit *shad,
		t_intersect inter)
{
	ray->origin = vector_op(ray->origin, vector_op(ray->direction,
					new_vector_3d_unicoord(ray->maxdist), '*'), '+');
	shad->actual_dist -= ray->maxdist;
	ray->maxdist = shad->actual_dist;
	ray->previous_inter_id = inter.shape_copy.id;
}

int					transparency(t_all *param, t_ray ray, int fastmode)
{
	int			trans_color;
	t_intersect	intersection;

	trans_color = 0;
	if ((get_nearest_intersection(&ray, param->scene, &intersection, DIST_MAX)))
	{
		if (fastmode == 1)
			return (intersection.shape_copy.color);
		if (param->data.filter == 4)
			intersection.normal = normalize(intersection.normal);
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

int					shadow_transp(t_all *param, t_ray ray, int start_color)
{
	t_shadunit	shad;
	t_intersect	inter;
	int			next_point;

	shad = new_shadunit(&ray);
	if (get_nearest_intersection(&ray, param->scene, &inter, ray.maxdist))
	{
		if (inter.shape_copy.opacity == 1.0)
			shad.shad_color = 0;
		else
		{
			if (shad.actual_id != inter.shape_copy.id)
			{
				shad.shad_color = interpolate(inter.shape_copy.color, 0,
						inter.shape_copy.opacity);
				shad.shad_color = interpolate(start_color, shad.shad_color,
							inter.shape_copy.opacity);
			}
			update_ray_data(&ray, &shad, inter);
			next_point = shadow_transp(param, ray, shad.shad_color);
			shad.shad_color = next_point == -1 ? shad.shad_color : next_point;
		}
	}
	return (shad.shad_color);
}
