/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_adapter.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cpieri <cpieri@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/16 14:45:18 by tmilon            #+#    #+#             */
/*   Updated: 2018/06/04 17:01:12 by cpieri           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"
#include <math.h>

t_ray	adapt_ray(t_ray ray, t_mat3d mat)
{
	ray.origin = adjust_direction(ray.origin, mat);
	ray.direction = adjust_direction(ray.direction, mat);
	ray.direction = normalize(ray.direction);
	return (ray);
}
