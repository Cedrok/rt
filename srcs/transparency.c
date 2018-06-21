/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   transparency.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmilon <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/21 10:22:20 by tmilon            #+#    #+#             */
/*   Updated: 2018/06/21 11:49:55 by tmilon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

int			transparency(t_all *param, t_ray ray)
{
	int	trans_color;
	t_intersect	intersection;

	trans_color = 0;
	if (get_nearest_intersection(&ray, param->scene, &intersection, DIST_MAX))
	{
		trans_color = set_color(param, intersection);
		if (intersection.shape_copy.opacity != 1)
		{
			ray.previous_inter_id = intersection.shape_copy.id;
			trans_color = interpolate(transparency(param, ray),
					trans_color, intersection.shape_copy.opacity);
		}
	}
	return (trans_color);
}
