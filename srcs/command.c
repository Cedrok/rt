/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cpieri <cpieri@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/22 10:01:24 by cpieri            #+#    #+#             */
/*   Updated: 2018/06/28 14:31:09 by cvautrai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

void		color_btn_mv(t_bloc *bc)
{
	int		i;
	t_color	color;

	i = 0;
	color = new_color(158, 158, 158);
	while (i < 12)
	{
		if (i == 2 || i == 4 || i == 7 || i == 6)
			color = new_color(0xd6, 0x11, 0x11);
		else if (i == 0 || i == 1 || i == 10 || i == 11)
			color = new_color(0x00, 0x95, 0xaa);
		else if (i == 5 || i == 3 || i == 8 || i == 9)
			color = new_color(0x39, 0xb5, 0x4a);
		((t_button*)bc->lst_obj[i]->obj)->color = color;
		i++;
	}
}

static int	m_value(int value, int c)
{
	value += (c == '+') ? 1 : -1;
	return (value);
}

t_shape		*get_shape_with_id(int id, t_scene sc)
{
	t_shape	*shape;

	while (sc.shape_lst != NULL)
	{
		shape = (t_shape*)sc.shape_lst->content;
		if (shape->type == -1)
			break ;
		if (shape->id == id)
			break ;
		sc.shape_lst = sc.shape_lst->next;
	}
	return (shape);
}

void		move_shape(void *p, int type)
{
	t_all	*param;
	t_scene	sc;
	t_shape	*shape;

	param = (t_all*)p;
	sc = param->scene;
	shape = get_shape_with_id(param->ui.g_id, sc);
	if (type == 3 || type == 5)
		shape->origin.y = (type == 3) ? m_value(shape->origin.y, '-') :
			m_value(shape->origin.y, '+');
	if (type == 2 || type == 4)
		shape->origin.x = (type == 2) ? m_value(shape->origin.x, '-') :
			m_value(shape->origin.x, '+');
	if (type == 0 || type == 1)
		shape->origin.z = (type == 1) ? m_value(shape->origin.z, '-')
			: m_value(shape->origin.z, '+');
	refresh_img(param);
}
