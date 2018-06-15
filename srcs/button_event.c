/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   button_event.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cpieri <cpieri@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/03 14:06:51 by cpieri            #+#    #+#             */
/*   Updated: 2018/06/06 10:27:54 by cpieri           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

static void	check_btn(t_bloc *bc, int x, int y)
{
	t_vector2d	lst_pt;
	t_button	*btn;
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
				if (x >= btn->pos.x && x <= lst_pt.x && y >= btn->pos.y && y <= lst_pt.y)
					ft_putendl("Welcome Delay");
			}
			i++;
		}
}

void	event_button(t_all *param, int x, int y)
{
	check_btn(param->ui.bc_rght, x, y);
	check_btn(param->ui.bc_center, x, y);
	check_btn(param->ui.bc_lft, x, y);
}