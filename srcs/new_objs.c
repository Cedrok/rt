/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   new_objs.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cpieri <cpieri@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/15 11:04:58 by cvautrai          #+#    #+#             */
/*   Updated: 2018/06/18 08:52:00 by cpieri           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

void	new_shape(void *p, int type)
{
	t_shape	new;
	t_all	*param;

	param = (t_all*)p;
	new = default_shape(type);
	new.origin = param->scene.camera.origin;
	new.origin.z += 5;
	ft_lstadd(&param->scene.shape_lst, ft_lstnew(&new, sizeof(new)));
	refresh_img(param);
}

void	new_spot(void *p, int c)
{
	t_light	new;
	t_all	*param;

	c = 0;
	param = (t_all*)p;
	new = default_light();
	new.origin = param->scene.camera.origin;
	new.origin.z += 5;
	ft_lstadd(&param->scene.light_lst, ft_lstnew(&new, sizeof(new)));
	refresh_img(param);
}
