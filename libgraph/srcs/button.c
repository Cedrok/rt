/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   button.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cpieri <cpieri@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/03 13:24:25 by cpieri            #+#    #+#             */
/*   Updated: 2018/06/06 10:23:49 by cpieri           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "button.h"

t_button	new_button(char *title, t_color color, int pos, int ratio)
{
	t_button	new_butn;

	new_butn.name = title;
	new_butn.color = color;
	new_butn.is_center = pos;
	new_butn.ratio_2 = ratio;
	return (new_butn);
}

void		set_btn_callback(t_button *btn, void (*clback)(void *), void *p)
{
	btn->callback = clback;
	btn->cllbck_param = p;
}
