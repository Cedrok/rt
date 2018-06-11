/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   button.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cpieri <cpieri@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/03 13:24:25 by cpieri            #+#    #+#             */
/*   Updated: 2018/06/08 18:06:19 by cpieri           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "button.h"
#include <stdio.h>

t_button	*new_button(t_vector4d parent_pos, t_color c, t_vector4d ratio_marge, int pos)
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

void		set_btn_callback(t_button *btn, void (*clback)(void *), void *p)
{
	btn->callback = clback;
	btn->cllbck_param = p;
}

void		set_title_btn(t_button *btn, char *title, t_vector4d pos, t_color c)
{
	int		font_size;

	font_size = (btn->pos.w * pos.y / 100);
	btn->title = new_label(title, c, pos, font_size);
}
