/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rotation_matrix.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cpieri <cpieri@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/01 15:31:44 by cpieri            #+#    #+#             */
/*   Updated: 2018/06/03 14:41:55 by cpieri           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "matrix.h"

void	identity_mat(t_mat3d *mat)
{
	mat->rgt = new_vector_3d(1, 0, 0);
	mat->up = new_vector_3d(0, 1, 0);
	mat->fwd = new_vector_3d(0, 0, 1);
}

void	rotate_x(t_mat3d *mat, double a)
{
	a *= DEG2RAD;
	mat->rgt = new_vector_3d(1, 0, 0);
	mat->up = new_vector_3d(0, cos(a), -sin(a));
	mat->fwd = new_vector_3d(0, sin(a), cos(a));
}

void	rotate_y(t_mat3d *mat, double a)
{
	a *= DEG2RAD;
	mat->rgt = new_vector_3d(cos(a), 0, sin(a));
	mat->up = new_vector_3d(0, 1, 0);
	mat->fwd = new_vector_3d(-sin(a), 0, cos(a));
}

void	rotate_z(t_mat3d *mat, double a)
{
	a *= DEG2RAD;
	mat->rgt = new_vector_3d(cos(a), -sin(a), 0);
	mat->up = new_vector_3d(sin(a), cos(a), 0);
	mat->fwd = new_vector_3d(0, 0, 1);
}

t_mat3d	matrix_inv(t_mat3d mat)
{
	t_mat3d	ret;
	double	det;

	det = matrix_det(mat);
	if (det != 0)
	{
		ret.rgt = new_vector_3d((mat.up.y * mat.fwd.z)
				- (mat.up.z * mat.fwd.y), (mat.rgt.z * mat.fwd.y)
				- (mat.rgt.y * mat.fwd.z), (mat.rgt.y * mat.up.z)
				- (mat.rgt.z * mat.up.y));
		ret.up = new_vector_3d((mat.up.z * mat.fwd.x)
				- (mat.up.x * mat.fwd.z), (mat.rgt.x * mat.fwd.z)
				- (mat.rgt.z * mat.fwd.x), (mat.rgt.z * mat.up.x)
				- (mat.rgt.x * mat.up.z));
		ret.fwd = new_vector_3d((mat.up.x * mat.fwd.y)
				- (mat.up.y * mat.fwd.x), (mat.rgt.y * mat.fwd.x)
				- (mat.rgt.x * mat.fwd.y), (mat.rgt.x * mat.up.y)
				- (mat.rgt.y * mat.up.x));
		ret.rgt = vector_op(ret.rgt, new_vector_3d_unicoord(1.0 / det), '*');
		ret.up = vector_op(ret.up, new_vector_3d_unicoord(1.0 / det), '*');
		ret.fwd = vector_op(ret.fwd, new_vector_3d_unicoord(1.0 / det), '*');
		return (ret);
	}
	return (mat);
}
