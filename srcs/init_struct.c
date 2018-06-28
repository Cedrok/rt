/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_struct.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cpieri <cpieri@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/06 11:55:34 by tmilon            #+#    #+#             */
/*   Updated: 2018/06/28 09:44:28 by tmilon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"
#include <math.h>

t_point	new_point(int x, int y, int color)
{
	t_point ret;

	ret.x = x;
	ret.y = y;
	ret.color = color;
	return (ret);
}

t_ray	new_ray(t_vector3d o, t_vector3d d)
{
	t_ray	ret;

	ret.origin = o;
	ret.direction = d;
	ret.previous_inter_id = -1;
	ret.normal_dir = 1;
	ret.maxdist = DIST_MAX;
	return (ret);
}

t_scene	new_scene(t_list *shape_lst, t_list *light_lst)
{
	t_scene		ret;

	ret.shape_lst = shape_lst;
	ret.light_lst = light_lst;
	return (ret);
}
