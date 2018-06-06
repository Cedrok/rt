/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   limit.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmilon <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/27 17:20:02 by tmilon            #+#    #+#             */
/*   Updated: 2018/06/06 10:37:53 by tmilon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

static t_calcunit	limiter_setup(t_shape shape, t_ray ray, t_calcunit calc)
{
	calc.get_in.x = shape.origin.x + (calc.t0 * ray.direction.x);
	calc.get_in.y = shape.origin.y + (calc.t0 * ray.direction.y);
	calc.get_in.z = shape.origin.z + (calc.t0 * ray.direction.z);
	calc.get_out.x = shape.origin.x + (calc.t1 * ray.direction.x);
	calc.get_out.y = shape.origin.y + (calc.t1 * ray.direction.y);
	calc.get_out.z = shape.origin.z + (calc.t1 * ray.direction.z);
	return (calc);
}

void		limit_sphere(t_shape shape, t_ray ray, double *t, t_calcunit calc)
{
	t_vector3d	min;
	t_vector3d	max;

	calc = limiter_setup(shape, ray, calc);
	min = new_vector_3d_unicoord(-shape.radius);
	max = new_vector_3d(1, 1, 1);
	max = vector_op(max, new_vector_3d_unicoord(shape.radius), '*');
	if (calc.t0 != -1
			&& calc.get_in.x >= min.x && calc.get_in.x < max.x
			&& calc.get_in.y >= min.y && calc.get_in.y < max.y
			&& calc.get_in.z >= min.z && calc.get_in.z < max.z
			)
		*t = calc.t0;
	else if (calc.t1 != -1
			&& calc.get_out.x >= min.x && calc.get_out.x < max.x
			&& calc.get_out.y >= min.y && calc.get_out.y < max.y
			&& calc.get_out.z >= min.z && calc.get_out.z < max.z
			)
		*t = calc.t1;
}

void		limit_cylinder(t_shape shape, t_ray ray, double *t, t_calcunit calc)
{
	t_vector3d	min;
	t_vector3d	max;

	calc = limiter_setup(shape, ray, calc);
	min = new_vector_3d(-shape.radius, 0, -shape.radius);
	max = new_vector_3d(1, 1, 1);
	max = vector_op(max, new_vector_3d(shape.radius, shape.height, shape.radius), '*');
	if (calc.t0 != -1
			&& calc.get_in.x >= min.x && calc.get_in.x < max.x
			&& calc.get_in.y >= min.y && calc.get_in.y < max.y
			&& calc.get_in.y < shape.height
			&& calc.get_in.z >= min.z && calc.get_in.z < max.z
			)
		*t = calc.t0;
	else if (calc.t1 != -1
			&& calc.get_out.x >= min.x && calc.get_out.x < max.x
			&& calc.get_out.y >= min.y && calc.get_out.y < max.y
			&& calc.get_out.y < shape.height
			&& calc.get_out.z >= min.z && calc.get_out.z < max.z
			)
		*t = calc.t1;
}

void		limit_cone(t_shape shape, t_ray ray, double *t, t_calcunit calc)
{
	t_vector3d	min;
	t_vector3d	max;

	calc = limiter_setup(shape, ray, calc);
	min = new_vector_3d(-shape.height, 0, -shape.height);
	max = new_vector_3d(1, 1, 1);
	max = vector_op(max, new_vector_3d_unicoord(shape.height), '*');
	if (calc.t0 != -1
			&& calc.get_in.x >= min.x && calc.get_in.x < max.x
			&& calc.get_in.y >= min.y && calc.get_in.y < max.y
			&& calc.get_in.y < shape.height
			&& calc.get_in.z >= min.z && calc.get_in.z < max.z
			)
		*t = calc.t0;
	else if (calc.t1 != -1
			&& calc.get_out.x >= min.x && calc.get_out.x < max.x
			&& calc.get_out.y >= min.y && calc.get_out.y < max.y
			&& calc.get_out.y < shape.height
			&& calc.get_out.z >= min.z && calc.get_out.z < max.z
			)
		*t = calc.t1;
}
