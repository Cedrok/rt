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

void	event_button(t_all *param, int x, int y)
{
	int 			b_x;
	int 			b_y;
	int 			b_z;
	int 			b_w;

	printf("pos_mouse.x = %d, pos_mouse.y = %d\n", x, y);
	b_x = param->btn_teste.pos.x;
	b_y = param->btn_teste.pos.y;
	b_z = param->btn_teste.pos.z;
	b_w = param->btn_teste.pos.w;
	printf("b_x = %d, b_x = %d, b_z = %d, b_w = %d\n", b_x, b_y, b_z, b_w);
	if (x >= b_x && x <= b_z && y >= b_y && y <= b_w)
	{
		printf("lol\n");
		param->data.filter = (param->data.filter < 4) ? param->data.filter + 1 : 0;
		clear_render(param->env);
		new_ui(param);
		put_filter(*param);
		param->env->rend = surface_2_rend(param->env);
	}
}