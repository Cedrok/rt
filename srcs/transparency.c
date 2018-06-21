/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   transparency.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmilon <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/21 10:22:20 by tmilon            #+#    #+#             */
/*   Updated: 2018/06/21 10:22:33 by tmilon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

int			transparency(t_all *param, t_ray ray, t_intersect intersection)
{
	int	trans_color;

	trans_color = 0;
	if (get_nearest_intersection(&ray, param->scene, &intersection, DIST_MAX))
	{
		trans_color = set_color(param, intersection);
		if (intersection.shape_copy.opacity != 1)
		{
			ray.previous_inter_id = intersection.shape_copy.id;
			trans_color = interpolate(transparency(param, ray, intersection),
					trans_color, intersection.shape_copy.opacity);
		}
	}
	return (trans_color);
}

