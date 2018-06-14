/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   intersection_torus.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Pringles <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/11 11:59:35 by Pringles          #+#    #+#             */
/*   Updated: 2018/06/14 10:37:38 by tmilon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

int	resolve_torus_eq(t_calcunit *calc, double *t)
{
	double	tmp;

	calc->delta = (calc->b * calc->b) - 4 * calc->a * calc->c;
	if (calc->delta < 0)
		return (0);
	calc->delta = sqrt(calc->delta);
	calc->t0 = (-calc->b - calc->delta) * 0.5 / calc->a;
	calc->t1 = (-calc->b + calc->delta) * 0.5 / calc->a;
	tmp = calc->t0;
	if (calc->t0 >= 0)
		calc->t0 = sqrt(calc->t0);
	if (calc->t1 >= 0)
		calc->t1 = sqrt(calc->t1);
	calc->t0 = (calc->t0 < *t && calc->t0 > DIST_MIN ? calc->t0 : -1);
	calc->t1 = (calc->t1 < *t && calc->t1 > DIST_MIN ? calc->t1 : -1);
	return (calc->t0 != -1 || calc->t1 == 0);
}

int	intersect_torus(t_shape shape, t_ray ray, double *t)
{
	t_calcunit	calc;

	shape.origin = adjust_direction(shape.origin, shape.inv_rot);
	shape.origin = vector_op(ray.origin, shape.origin, '-');
	calc.a = (ray.direction.x * ray.direction.x + ray.direction.y * ray.direction.y + ray.direction.z * ray.direction.z)
			* (ray.direction.x * ray.direction.x + ray.direction.y * ray.direction.y + ray.direction.z * ray.direction.z);
	calc.b = (ray.direction.x * shape.origin.x + ray.direction.y * shape.origin.y + ray.direction.z * shape.origin.z)
		* (shape.radius * shape.radius - shape.width * shape.width) - 2 * shape.radius * shape.radius * (ray.direction.x
		* shape.origin.x + ray.direction.y * shape.origin.y);
	calc.b *= 2;
	calc.c = (shape.radius * shape.radius - shape.width * shape.width) *
		(shape.radius * shape.radius - shape.width * shape.width);
	if (resolve_torus_eq(&calc, t))
		*t = (calc.t0 != -1 ? calc.t0 : calc.t1);
	return (*t == calc.t0 || *t == calc.t1);
}
