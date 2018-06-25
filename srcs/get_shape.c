/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_shape.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cpieri <cpieri@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/21 16:02:53 by tmilon            #+#    #+#             */
/*   Updated: 2018/06/25 14:16:21 by cvautrai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"
#include <stdlib.h>
#include <math.h>

static int		get_nearest_shape_id(t_ray *ray, t_scene scene)
{
	t_shape		shape;
	int			nearest_shape_id;
	double		maxdist;

	maxdist = DIST_MAX;
	nearest_shape_id = -1;
	while (scene.shape_lst != NULL)
	{
		shape = *(t_shape*)scene.shape_lst->content;
		if (shape.type == -1)
			break ;
		if (collisions(shape, adapt_ray(*ray, shape.inv_rot), &maxdist))
			nearest_shape_id = shape.id;
		scene.shape_lst = scene.shape_lst->next;
	}
	return (nearest_shape_id);
}

static t_ray	get_ray_on_clic(int x, int y, t_camera *cam, t_all *param)
{
	t_vector3d	axe;
	t_ray		ray;

	axe = set_axe(x, y, cam, param->env->surf);
	ray = new_ray(cam->origin, axe);
	return (ray);
}

static void		highlight(t_all *param, int id)
{
	t_shape	*shape;
	t_list	*head;

	head = param->scene.shape_lst;
	while (param->scene.shape_lst != NULL)
	{
		shape = (t_shape*)param->scene.shape_lst->content;
		if (shape->id == id)
			shape->color = 0x23FF23;
		else
			shape->color = shape->base_color;
		param->scene.shape_lst = param->scene.shape_lst->next;
	}
	param->scene.shape_lst = head;
	refresh_img(param);
}

void			select_shape(t_all *param, int x, int y)
{
	t_ray	ray;

	ray = get_ray_on_clic(x, y, &param->scene.camera, param);
	param->ui.g_id = get_nearest_shape_id(&ray, param->scene);
	highlight(param, param->ui.g_id);
}
