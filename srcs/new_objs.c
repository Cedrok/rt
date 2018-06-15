/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   new_objs.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cvautrai <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/15 11:04:58 by cvautrai          #+#    #+#             */
/*   Updated: 2018/06/15 11:34:18 by cvautrai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

void	new_shape(int type, t_scene *sc)
{
	t_shape	new;

	new = default_shape(type);
	new.origin = sc->camera.origin;
	new.origin.z += 5;
	ft_lstadd(&sc->shape_lst, ft_lstnew(&new, sizeof(new)));
}

void	new_spot(t_scene *sc)
{
	t_light	new;

	new = default_light();
	new.origin = sc->camera.origin;
	new.origin.z += 5;
	ft_lstadd(&sc->light_lst, ft_lstnew(&new, sizeof(new)));
}
