/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector_new.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cpieri <cpieri@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/01 15:17:23 by cpieri            #+#    #+#             */
/*   Updated: 2018/06/03 14:43:05 by cpieri           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vector.h"

t_vector3d	new_vector_3d_unicoord(double value)
{
	t_vector3d	ret;

	ret.x = value;
	ret.y = value;
	ret.z = value;
	return (ret);
}

t_vector3d	new_vector_3d(double x, double y, double z)
{
	t_vector3d	ret;

	ret.x = x;
	ret.y = y;
	ret.z = z;
	return (ret);
}

t_vector4d	new_vector_4d(double x, double y, double z, double w)
{
	t_vector4d	a;

	a.x = x;
	a.y = y;
	a.z = z;
	a.w = w;
	return (a);
}

t_vector2d	new_vector_2d(double x, double y)
{
	t_vector2d	a;

	a.x = x;
	a.y = y;
	return (a);
}
