/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ui.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cpieri <cpieri@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/30 11:06:00 by cpieri            #+#    #+#             */
/*   Updated: 2018/06/06 10:27:24 by cpieri           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

void		draw_btn_render(t_button btn, SDL_Renderer *rend)
{
	t_vector2d	point;

	point = new_vector_2d(-1, -1);
	while (++point.y < btn.pos.w)
	{
		point.x = -1;
		while (++point.x < btn.pos.z)
		{
			SDL_SetRenderDrawColor(rend, btn.color.r,
				btn.color.g, btn.color.b, 255);
			SDL_RenderDrawPoint(rend, btn.pos.x + point.x, btn.pos.y + point.y);
		}
	}
}

void		draw_bloc_render(t_bloc bloc, SDL_Renderer *rend)
{
	t_vector2d	point;

	point = new_vector_2d(-1, -1);
	while (++point.y < bloc.pos.w)
	{
		point.x = -1;
		while (++point.x < bloc.pos.z)
		{
			SDL_SetRenderDrawColor(rend, bloc.color.r,
				bloc.color.g, bloc.color.b, 255);
			SDL_RenderDrawPoint(rend, bloc.pos.x + point.x, bloc.pos.y + point.y);
		}
	}
}

t_bloc		create_bloc_filter(t_all *param)
{
	int			ratio;
	int			margin;
	t_bloc		bloc_1;
	t_vector4d	btn_1_pos;
	t_vector2d	left_p;
	int 		x, y;

	ratio = 18;
	margin = 2;
	SDL_GetWindowSize(param->env->win, &x, &y);
	left_p.x = x - (x * ratio / 100) - (x * margin / 100);
	left_p.y = 0 + (y * margin / 100);
	btn_1_pos = new_vector_4d(left_p.x, left_p.y, (x * ratio / 100), (y * ratio / 100));
	bloc_1 = create_new_bloc("first bloc", btn_1_pos, new_color(0x00, 0x3c, 0x40), 16);
	t_button btn = new_button("sepia", new_color(0, 255, 130), CENTER, 50);
	btn.pos = set_child_size(&bloc_1, btn.is_center, btn.ratio_2, 0);
	draw_bloc_render(bloc_1, param->env->rend);
	draw_btn_render(btn, param->env->rend);
	return (bloc_1);
}

int	    	new_ui(t_all *param)
{
	t_bloc		bc_filter;

	bc_filter = create_bloc_filter(param);
	return (0);
}
