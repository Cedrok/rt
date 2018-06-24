/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cpieri <cpieri@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/01 13:03:51 by cpieri            #+#    #+#             */
/*   Updated: 2018/06/24 17:54:02 by bspindle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef VECTOR_H
# define VECTOR_H

typedef struct	s_vector3d
{
	double		x;
	double		y;
	double		z;
}				t_vector3d;

typedef struct	s_vector4d
{
	double		x;
	double		y;
	double		z;
	double		w;
}				t_vector4d;

typedef struct	s_vector2d
{
	double		x;
	double		y;
}				t_vector2d;

t_vector3d		new_vector_3d(double x, double y, double z);
t_vector3d		new_vector_3d_unicoord(double value);
t_vector4d		new_vector_4d(double x, double y, double z, double w);
t_vector2d		new_vector_2d(double x, double y);
t_vector3d		cross(t_vector3d a, t_vector3d b);
t_vector3d		normalize(t_vector3d v);
t_vector3d		vector_op(t_vector3d a, t_vector3d b, char type);
t_vector2d		vector_op_2d(t_vector2d a, t_vector2d b, char type);
t_vector3d		vectorial_prod(t_vector3d a, t_vector3d b);
t_vector3d		find_normal_vect(t_vector3d u);
t_vector3d		lambda_product_d3(double lambda, t_vector3d vector);
t_vector2d		lambda_product_d2(double lambda, t_vector2d vector);
double			dotprod(t_vector3d a, t_vector3d b);
double			dotprod_2d(t_vector2d a, t_vector2d b);
double			distance_d3(t_vector3d a, t_vector3d b);
double			get_length(t_vector3d v);

#endif
