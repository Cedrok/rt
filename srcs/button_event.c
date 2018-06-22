/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   button_event.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cpieri <cpieri@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/03 14:06:51 by cpieri            #+#    #+#             */
/*   Updated: 2018/06/22 15:19:12 by cpieri           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

static void	check_btn(t_bloc *bc, t_all *param, int x, int y)
{
	t_vector2d	lst_pt;
	t_button	*btn;
	void		(*test)(void *, int);
	int			i;

	i = 0;
	if (bc->lst_obj != NULL)
		while (bc->lst_obj[i] != NULL)
		{
			if (bc->lst_obj[i]->type == BUTTON)
			{
				btn = ((t_button*)bc->lst_obj[i]->obj);
				lst_pt.x = btn->pos.x + btn->pos.z;
				lst_pt.y = btn->pos.y + btn->pos.w;
				test = btn->f;
				if (test != NULL && x >= btn->pos.x && x <= lst_pt.x &&
						y >= btn->pos.y && y <= lst_pt.y)
					(*test)(param, btn->type);
			}
			i++;
		}
}

void		event_button(t_all *param, int x, int y)
{
	t_vector4d	rend_s;
	t_vector2d	lst_p;

	rend_s = size_rend(param->env->w, param->env->h);
	lst_p.x = rend_s.x + rend_s.z;
	lst_p.y = rend_s.y + rend_s.w;
	check_btn(param->ui.bc_rght, param, x, y);
	check_btn(param->ui.bc_center, param, x, y);
	check_btn(param->ui.bc_lft, param, x, y);
	if (x >= rend_s.x && x <= lst_p.x && y >= rend_s.y && y <= lst_p.y)
		select_shape(param, x, y);
}
