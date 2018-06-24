/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cpieri <cpieri@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/18 19:35:43 by tmilon            #+#    #+#             */
/*   Updated: 2018/06/24 17:52:58 by bspindle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vector.h"
#include <math.h>

double		get_length(t_vector3d v)
{
	return (sqrt(v.x * v.x + v.y * v.y + v.z * v.z));
}

t_vector3d	normalize(t_vector3d v)
{
	double	length;

	length = get_length(v);
	return (new_vector_3d(v.x / length, v.y / length, v.z / length));
}

double		distance_d3(t_vector3d a, t_vector3d b)
{
	double	d;

	d = sqrt((a.x - b.x) * (a.x - b.x) + (a.y - b.y) * (a.y - b.y)
			+ (a.z - b.z) * (a.z - b.z));
	return (d);
}

double		distance_d2(t_vector2d a, t_vector2d b)
{
	double	d;

	d = sqrt((a.x - b.x) * (a.x - b.x) + (a.y - b.y) * (a.y - b.y));
	return (d);
}

t_vector3d	vector_op(t_vector3d a, t_vector3d b, char type)
{
	if (type == '-')
		return (new_vector_3d(a.x - b.x, a.y - b.y, a.z - b.z));
	else if (type == '*')
		return (new_vector_3d(a.x * b.x, a.y * b.y, a.z * b.z));
	else if (type == '/')
		return (new_vector_3d(a.x / b.x, a.y / b.y, a.z / b.z));
	return (new_vector_3d(a.x + b.x, a.y + b.y, a.z + b.z));
}
