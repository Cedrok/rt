/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   transparency.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmilon <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/21 10:22:20 by tmilon            #+#    #+#             */
/*   Updated: 2018/06/21 13:09:30 by tmilon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

int			transparency(t_all *param, t_ray ray, int fastmode)
{
	int	trans_color;
	double	maxdist;
	t_intersect	intersection;

	trans_color = 0;
	if ((maxdist = get_nearest_intersection(&ray, param->scene, &intersection, DIST_MAX)))
	{
		if (fastmode == 1)
			return (intersection.shape_copy.color);
		trans_color = set_color(param, intersection);
		if (intersection.shape_copy.opacity != 1)
		{
			ray.origin = vector_op(ray.origin, vector_op(ray.direction,
					new_vector_3d_unicoord(maxdist), '*'), '+');
			ray.previous_inter_id = intersection.shape_copy.id;
			trans_color = interpolate(transparency(param, ray, fastmode),
					trans_color, intersection.shape_copy.opacity);
		}
	}
	return (trans_color);
}

/*
int				shadow_transp(t_ray ray, t_intersect inter, t_light light, double dist)
{
	double	tmp;

	if ((tmp = get_nearest_intersection(&ray, scene, &inter, dist)))
	{
		if (inter.shape_copy.opacity != 1.0)
		{
			inter.shape_copy.color = interpolate(0, inter.shape_copy.color,
				ftb_clamp( 1 - inter.shape_copy.opacity, 0, 1));
			*color = interpolate(inter.shape_copy.color, *color,
				ftb_clamp(1 - inter.shape_copy.opacity, 0, 1));
		}
		*color = interpolate(0, *color, ftb_clamp(param->data.ambiantlight + 1 - inter.shape_copy.opacity, 0, 1));
		if (inter.shape_copy.opacity != 1.0)
		{
			dist -= tmp;
			ray.origin = vector_op(ray.origin, vector_op(ray.direction,
					new_vector_3d_unicoord(tmp), '*'), '+');
			ray.previous_inter_id = inter.shape_copy.id;
			*color = interpolate(shadow_transp(ray, inter, light, dist), color, inter.shape_copy.opacity);
		}
		else
			return (1);
	}
	return (0);
}*/
