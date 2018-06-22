/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cpieri <cpieri@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/22 10:01:24 by cpieri            #+#    #+#             */
/*   Updated: 2018/06/22 13:53:55 by cvautrai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

void	on_move(void *p, int type)
{
	t_all		*param;
	t_button	*on;
	t_color		white;
	t_vector4d	btn_s;

	param = (t_all*)p;
	white = new_color(0xff, 0xff, 0xff);
	btn_s = new_vector_4d(101, 55, 0, 0);
	on = ((t_button*)param->ui.bc_lft->lst_obj[0]->obj);
	on->type = (type == 1) ? 0 : 1;
	if (type == 0)
	{
		on->color = new_color(0, 0x42, 0x19);
		set_title_btn(on, "Move Obj: ON", btn_s, white);
	}
	if (type == 1)
	{
		on->color = new_color(0x42, 0, 0x19);
		set_title_btn(on, "Move Obj: OFF", btn_s, white);
	}
	refresh_surf(param, param->data.filter);
}
