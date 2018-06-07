/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   obj_lst.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cpieri <cpieri@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/06 10:34:26 by cpieri            #+#    #+#             */
/*   Updated: 2018/06/06 10:34:44 by cpieri           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "bloc.h"

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