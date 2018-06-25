/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   normal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cpieri <cpieri@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/19 17:51:48 by tmilon            #+#    #+#             */
/*   Updated: 2018/06/25 09:34:25 by bspindle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

t_vector3d	sphere_normal(t_shape shape, t_vector3d intersection_point)
{
	(void)shape;
	return (intersection_point);
}

t_vector3d	plane_normal(t_shape shape, t_vector3d intersection_point)
{
	(void)shape;
	(void)intersection_point;
	return (new_vector_3d(0, 1, 0));
}

t_vector3d	cylinder_normal(t_shape shape, t_vector3d intersection_point)
{
	t_vector3d	normal;

	(void)shape;
	normal = new_vector_3d(intersection_point.x, 0, intersection_point.z);
	return (normal);
}

t_vector3d	cone_normal(t_shape shape, t_vector3d intersection_point)
{
	t_vector3d	normal;

	normal = new_vector_3d(intersection_point.x, shape.radius,
			intersection_point.z);
	return (normal);
}
