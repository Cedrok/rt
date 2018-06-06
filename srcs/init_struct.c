/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_struct.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cpieri <cpieri@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/06 11:55:34 by tmilon            #+#    #+#             */
/*   Updated: 2018/06/04 17:01:18 by cpieri           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"
#include <math.h>

t_light	new_light(t_vector3d origin, double intensity, int color)
{
	t_light	ret;

	ret.origin = origin;
	ret.intensity = intensity;
	ret.color = color;
	return (ret);
}

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
	return (ret);
}

t_scene	new_scene(t_list *shape_lst, t_list *light_lst)
{
	t_scene		ret;

	ret.shape_lst = shape_lst;
	ret.light_lst = light_lst;
	return (ret);
}
