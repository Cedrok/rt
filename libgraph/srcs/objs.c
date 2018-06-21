/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   objs.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cvautrai <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/21 14:12:09 by cvautrai          #+#    #+#             */
/*   Updated: 2018/06/21 14:14:26 by cvautrai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "bloc.h"

t_obj		*new_obj(void *obj, size_t obj_size, int type)
{
	t_obj	*new;

	if (!(new = (t_obj*)ft_memalloc(sizeof(t_obj))))
		return (NULL);
	new->obj = obj;
	new->obj_size = obj_size;
	new->type = type;
	return (new);
}

int			init_lstobj(t_bloc *bloc, int size)
{
	if (!(bloc->lst_obj = (t_obj**)malloc(sizeof(t_obj*) * (size + 1))))
		return (0);
	bloc->lst_obj[size] = NULL;
	return (1);
}
