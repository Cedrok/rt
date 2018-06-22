/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bloc.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cpieri <cpieri@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/04 10:50:45 by cpieri            #+#    #+#             */
/*   Updated: 2018/06/22 11:56:12 by cpieri           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "bloc.h"

static void	set_left_p_rdc(t_vector2d *left_p, t_vector4d parent_size,
		t_vector2d size, t_vector2d margin)
{
	left_p->x = parent_size.z - size.x - margin.x;
	left_p->y = parent_size.w - size.y - margin.y;
}

static void	set_left_p_center(t_vector2d *left_p, t_vector4d parent_size,
		t_vector2d size)
{
	left_p->x = (parent_size.x + (parent_size.z / 2)) - (size.x / 2);
	left_p->y = (parent_size.y + (parent_size.w / 2)) - (size.y / 2);
}

t_vector4d	calc_position(t_vector4d parent_size, t_vector4d ratio_marge,
		int pos)
{
	t_vector2d	margin;
	t_vector2d	left_p;
	t_vector2d	size;

	size.x = (parent_size.z * ratio_marge.x / 100);
	size.y = (parent_size.w * ratio_marge.y / 100);
	margin.x = (parent_size.z * ratio_marge.z / 100);
	margin.y = (parent_size.w * ratio_marge.w / 100);
	left_p.x = parent_size.x + margin.x;
	left_p.y = parent_size.y + margin.y;
	left_p.y = (pos == LEFT_DOWN_CONER) ?
		parent_size.w - size.y - margin.y : left_p.y;
	left_p.x = (pos == RIGHT_UP_CONER) ?
		parent_size.z - size.x - margin.x : left_p.x;
	if (pos == RIGHT_DOWN_CONER)
		set_left_p_rdc(&left_p, parent_size, size, margin);
	left_p.y = (pos == VERTICAL_CENTER) ?
		(parent_size.y + (parent_size.w / 2)) - (size.y / 2) : left_p.y;
	left_p.x = (pos == HORIZONTAL_CENTER) ?
		(parent_size.x + (parent_size.z / 2)) - (size.x / 2) : left_p.x;
	if (pos == CENTER)
		set_left_p_center(&left_p, parent_size, size);
	return (new_vector_4d(left_p.x, left_p.y, size.x, size.y));
}

t_bloc		*new_bloc(t_vector2d w_sz, t_color c, t_vector4d r_m, int pos)
{
	t_bloc		*new;

	if (!(new = (t_bloc*)malloc(sizeof(t_bloc))))
		return (NULL);
	new->pos = calc_position(new_vector_4d(0, 0, w_sz.x, w_sz.y), r_m, pos);
	new->color = c;
	new->title = new_label(NULL, c, new_vector_4d(0, 0, 0, 0), 0);
	new->lst_obj = NULL;
	return (new);
}

void		set_title_bloc(t_bloc *bloc, char *title, t_vector4d pos, t_color c)
{
	int		font_size;

	font_size = (bloc->pos.w * pos.y / 100) / 3;
	bloc->title = new_label(title, c, pos, font_size);
}
