/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   is_in.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bspindle <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/01 14:50:24 by bspindle          #+#    #+#             */
/*   Updated: 2018/06/25 09:15:04 by bspindle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

int		is_in_sphere(t_shape sphere, t_light light)
{
	if (distance_d3(sphere.origin, light.origin) == sphere.radius)
		return (1);
	return (0);
}

int		is_in_cylinder(t_shape cyl, t_light light)
{
	t_vector3d	tmp;

	tmp = vector_op(light.origin, lambda_product_d3(-1, cyl.origin), '+');
	tmp = adjust_direction(tmp, cyl.inv_rot);
	if (tmp.x * tmp.x + tmp.z * tmp.z == cyl.radius * cyl.radius)
		return (1);
	return (0);
}

int		is_in_cone(t_shape cone, t_light light)
{
	t_vector3d	tmp;
	double		cmp;

	tmp = vector_op(light.origin, lambda_product_d3(-1, cone.origin), '+');
	tmp = adjust_direction(tmp, cone.inv_rot);
	cmp = tan(cone.radius);
	if (tmp.x * tmp.x + tmp.z * tmp.z <= tmp.y * tmp.y * cmp * cmp)
		return (1);
	return (0);
}

int		is_in_plane(t_shape plane, t_light light)
{
	t_vector3d	tmp;
	double		cmp;

	tmp = vector_op(light.origin, lambda_product_d3(-1, plane.origin), '+');
	tmp = adjust_direction(tmp, plane.inv_rot);
	cmp = tmp.y;
	if (cmp == 0)
		return (1);
	return (0);
}

void	is_light_in(t_list *light_lst, t_list *shape_lst)
{
	t_shape	shape;
	t_light	*light;

	while (((t_light*)light_lst->content)->color != -1)
	{
		light = (t_light*)light_lst->content;
		while (((t_shape*)shape_lst->content)->type != -1)
		{
			shape = *(t_shape*)shape_lst->content;
			if (is_in(shape, *light))
			{
				light->is_hidden = 1;
				break ;
			}
			shape_lst = shape_lst->next;
		}
		if (((t_shape*)shape_lst->content)->type == -1)
			light->is_hidden = 0;
		light_lst = light_lst->next;
	}
}
