/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector_product.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cpieri <cpieri@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/01 15:03:11 by cpieri            #+#    #+#             */
/*   Updated: 2018/06/03 14:42:51 by cpieri           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vector.h"

t_vector3d	lambda_product_d3(double lambda, t_vector3d vector)
{
	t_vector3d	result;

	result.x = lambda * vector.x;
	result.y = lambda * vector.y;
	result.z = lambda * vector.z;
	return (result);
}

t_vector2d	lambda_product_d2(double lambda, t_vector2d vector)
{
	t_vector2d	result;

	result.x = lambda * vector.x;
	result.y = lambda * vector.y;
	return (result);
}

t_vector3d	vectorial_prod(t_vector3d a, t_vector3d b)
{
	t_vector3d	c;

	c.x = a.y * b.z - a.z * b.y;
	c.y = a.z * b.x - a.x * b.z;
	c.z = a.x * b.y - a.y * b.x;
	return (c);
}

t_vector3d	find_normal_vect(t_vector3d u)
{
	t_vector3d	v;

	if (u.x)
	{
		if (u.y)
			v = new_vector_3d(1, -u.x / u.y, 0);
		else
			v = new_vector_3d(0, 1, 0);
	}
	else if (u.y || u.z)
		v = new_vector_3d(1, 0, 0);
	else
		v = new_vector_3d(0, 0, 0);
	return (v);
}

double		dotprod(t_vector3d a, t_vector3d b)
{
	return (a.x * b.x + a.y * b.y + a.z * b.z);
}
