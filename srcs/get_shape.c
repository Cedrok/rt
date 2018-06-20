/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   display.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cpieri <cpieri@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/21 16:02:53 by tmilon            #+#    #+#             */
/*   Updated: 2018/06/20 17:22:59 by cvautrai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"
#include <stdlib.h>
#include <math.h>

static int		get_nearest_shape_id(t_ray *ray, t_scene scene)
{
	int			(*collisions[10])(t_shape shape, t_ray ray, double *t);
	t_shape		shape;
	t_shape		nearest_shape;

	collisions[SPHERE] = &intersect_sphere;
	collisions[PLANE] = &intersect_plane;
	collisions[CYLINDER] = &intersect_cylinder;
	collisions[CONE] = &intersect_cone;
	collisions[TORUS] = &intersect_torus;
	nearest_shape.color = 0;
	while (scene.shape_lst != NULL)
	{
		shape = *(t_shape*)scene.shape_lst->content;
		if (shape.type == -1)
			return (-1);
		if (ray->previous_inter_id != shape.id && collisions[shape.type](shape,
					adapt_ray(*ray, shape.inv_rot), &maxdist))
			nearest_shape = shape;
		scene.shape_lst = scene.shape_lst->next;
	}
	return (nearest_shape.id);
}

static t_ray	get_ray_on_clic(int x, int y, t_camera *cam)
{
	t_vector3d	axe;
	t_ray		ray;

	axe = set_axe(x, y, cam);
	ray = new_ray(cam->origin, axe);
	return (ray);
}

void			select_shape(t_all *param, int x, int y)
{
	t_ray	ray;
	int		id;

	ray = get_ray_on_clic(x, y, &(param->scene.cam));
	id = get_nearest_shape_id(&ray, param->scene);
}
