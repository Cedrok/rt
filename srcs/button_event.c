/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   button_event.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bocal <bocal@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/03 14:06:51 by cpieri            #+#    #+#             */
/*   Updated: 2018/06/15 17:14:18 by bocal            ###   ########.fr       */
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
				if (test != NULL && x >= btn->pos.x && x <= lst_pt.x && y >= btn->pos.y
					&& y <= lst_pt.y)
					(*test)(param, btn->type);
			}
			i++;
		}
}

void	event_button(t_all *param, int x, int y)
{
	check_btn(param->ui.bc_rght, param, x, y);
	check_btn(param->ui.bc_center, param, x, y);
	check_btn(param->ui.bc_lft, param, x, y);
}