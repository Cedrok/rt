/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   button.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cpieri <cpieri@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/03 13:24:25 by cpieri            #+#    #+#             */
/*   Updated: 2018/06/24 18:20:47 by cpieri           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "button.h"
#include <stdio.h>

t_button	*new_button(t_vector4d parent_pos, t_color c,
					t_vector4d ratio_marge, int pos)
{
	t_button	*new;

	if (!(new = (t_button*)ft_memalloc(sizeof(t_button))))
		return (NULL);
	new->color = c;
	new->pos = calc_position(parent_pos, ratio_marge, pos);
	new->ratio_marge = ratio_marge;
	new->title = new_label(NULL, c, new_vector_4d(0, 0, 0, 0), 0);
	return (new);
}

void		set_btn_callback(t_button *btn, void (*clback)(void *, int),
					void *p, int type)
{
	btn->type = type;
	btn->f = clback;
	btn->f_param = p;
}

void		set_title_btn(t_button *btn, char *title, t_vector4d pos, t_color c)
{
	int		font_size;

	font_size = (btn->pos.w * pos.y / 100);
	btn->title = new_label(title, c, pos, font_size);
}

void		change_btn_fs(t_vector2d win_s, t_button *btn, t_vector4d pos)
{
	int		font_size;
	double	format;

	format = win_s.x / win_s.y;
	if (format >= 1.33)
		font_size = (btn->pos.w * pos.y / 100);
	else
		font_size = (btn->pos.w * pos.y / 100) * 0.8;
	btn->title.font_size = font_size;
}
