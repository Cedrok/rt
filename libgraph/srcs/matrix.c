/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   matrix.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cpieri <cpieri@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/15 14:40:36 by cpieri            #+#    #+#             */
/*   Updated: 2018/06/03 14:42:27 by cpieri           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "matrix.h"

double				matrix_det(t_mat3d mat)
{
	double	res;

	res = 0;
	res += mat.rgt.x * mat.up.y * mat.fwd.z;
	res += mat.up.x * mat.fwd.y * mat.rgt.z;
	res += mat.fwd.x * mat.rgt.y * mat.up.z;
	res -= mat.rgt.x * mat.fwd.y * mat.up.z;
	res -= mat.fwd.x * mat.up.y * mat.rgt.z;
	res -= mat.up.x * mat.rgt.y * mat.fwd.z;
	return (res);
}

static t_vector3d	build_row(t_vector3d src, t_mat3d add)
{
	double	a;
	double	b;
	double	c;

	a = (src.x * add.rgt.x) + (src.y * add.up.x) + (src.z * add.fwd.x);
	b = (src.x * add.rgt.y) + (src.y * add.up.y) + (src.z * add.fwd.y);
	c = (src.x * add.rgt.z) + (src.y * add.up.z) + (src.z * add.fwd.z);
	return (new_vector_3d(a, b, c));
}

t_mat3d				matrix_mult(t_mat3d m1, t_mat3d m2)
{
	t_mat3d	ret;

	ret.rgt = build_row(m1.rgt, m2);
	ret.up = build_row(m1.up, m2);
	ret.fwd = build_row(m1.fwd, m2);
	return (ret);
}

t_vector3d			adjust_direction(t_vector3d src, t_mat3d mat)
{
	t_vector3d	ret;

	ret.x = mat.rgt.x * src.x + mat.rgt.y * src.y + mat.rgt.z * src.z;
	ret.y = mat.up.x * src.x + mat.up.y * src.y + mat.up.z * src.z;
	ret.z = mat.fwd.x * src.x + mat.fwd.y * src.y + mat.fwd.z * src.z;
	return (ret);
}

t_mat3d				new_matrix(double x, double y, double z)
{
	t_mat3d	ret;
	t_mat3d	tmp;

	identity_mat(&ret);
	rotate_x(&tmp, x);
	if (x)
		ret = matrix_mult(ret, tmp);
	rotate_y(&tmp, y);
	if (y)
		ret = matrix_mult(ret, tmp);
	rotate_z(&tmp, z);
	if (z)
		ret = matrix_mult(ret, tmp);
	return (ret);
}
