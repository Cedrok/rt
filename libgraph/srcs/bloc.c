/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bloc.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cpieri <cpieri@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/04 10:50:45 by cpieri            #+#    #+#             */
/*   Updated: 2018/06/06 09:15:44 by cpieri           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "bloc.h"

t_bloc			create_new_bloc(char *s, t_vector4d p, t_color c, int f_size)
{
	t_bloc	new;

	new.title = create_new_label(s, new_color(255,255,255), f_size);
	new.pos = p;
	new.color = c;
	return (new);
}

void			lst_add_obj(t_obj **alst, t_obj *new)
{
	if (alst && *alst)
		new->next = *alst;
	*alst = new;
}

t_obj			*new_lst_obj(const void *obj, size_t obj_size, int type)
{
	t_obj	*new;

	if ((new = (t_obj*)malloc(sizeof(t_obj))) == 0)
		return (NULL);
	if (obj)
	{
		new->obj = malloc(obj_size);
		if (!new->obj)
			return (NULL);
		ft_memcpy(new->obj, obj, obj_size);
		new->obj_size = obj_size;
		new->type = type;
	}
	else
	{
		new->obj = NULL;
		new->obj_size = 0;
		type = 0;
	}
	new->next = NULL;
	return (new);
}

t_vector4d		set_child_size(t_bloc *bloc, int pos, int ratio, int margin)
{
	t_vector2d		size;
	t_vector2d		left_p;

	size.x = bloc->pos.z * ratio / 100;
	size.y = bloc->pos.w * ratio / 100;
	margin = (margin != 0) ? (bloc->pos.x * margin / 100) : 0;
	left_p.x = bloc->pos.x + margin;
	margin = (margin != 0) ? (bloc->pos.y * margin / 100) : 0;
	left_p.y = bloc->pos.y + margin;
	if (pos == CENTER)
	{
		left_p.x = (bloc->pos.x + (bloc->pos.z / 2)) - (size.x / 2);
		left_p.y = (bloc->pos.y + (bloc->pos.w / 2)) - (size.y / 2);
	}
	else if (pos == VERTICAL_CENTER)
		left_p.y = (bloc->pos.y + (bloc->pos.w / 2)) - (size.y / 2);
	else if (pos == HORIZONTAL_CENTER)
		left_p.x = (bloc->pos.x + (bloc->pos.z / 2)) - (size.x / 2);
	return (new_vector_4d(left_p.x, left_p.y, size.x, size.y));
}
