/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   is_in.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bspindle <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/01 14:50:24 by bspindle          #+#    #+#             */
/*   Updated: 2018/06/24 17:59:36 by bspindle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

int	is_in_sphere(t_shape sphere, t_light light)
{
	if (distance_d3(sphere.origin, light.origin) == sphere.radius)
		return (1);
	return (0);
}

int	is_in_cylinder(t_shape cyl, t_light light)
{
	t_vector3d	tmp;

	tmp = vector_op(light.origin, lambda_product_d3(-1, cyl.origin), '+');
	tmp = adjust_direction(tmp, cyl.inv_rot);
	//tmp = rotx(cyl.axis.x, roty(cyl.axis.y, rotz(cyl.axis.z, tmp)));
	if (tmp.x * tmp.x + tmp.z * tmp.z == cyl.radius * cyl.radius)
		return (1);
	return (0);
}

int	is_in_cone(t_shape cone, t_light light)
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

int	is_in_plane(t_shape plane, t_light light)
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

void	is_light_in(t_scene *scene)
{
	//t_shape	shape;
	t_light	*light;
	int		(*is_in[10])(t_shape, t_light);

	is_in[SPHERE] = &is_in_sphere;
	is_in[CYLINDER] = &is_in_cylinder;
	is_in[CONE] = &is_in_cone;
	is_in[PLANE] = &is_in_plane;
	while (((t_light*)scene->light_lst->content)->color != -1)
	{
		light = (t_light*)scene->light_lst->content;
		/*while (((t_shape*)scene->shape_lst->content)->type != -1)
		{
			shape = *(t_shape*)scene->shape_lst->content;
			if (is_in[shape.type](shape, *light))
			{
				light->is_hidden = 1;
				break ;
			}
			scene->shape_lst = scene->shape_lst->next;
		}
		if (((t_shape*)scene->shape_lst->content)->type == -1)
			light->is_hidden = 0;*/
		scene->light_lst = scene->light_lst->next;
	}
}
