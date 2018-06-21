/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ui_filters.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cvautrai <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/21 11:52:05 by cvautrai          #+#    #+#             */
/*   Updated: 2018/06/21 11:56:05 by cvautrai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

static t_right	right_obj(t_vector4d p_pos)
{
	t_right		r;

	r.btn_def = new_button(p_pos, new_color(42, 101, 0x19),
		new_vector_4d(90, 5, 2, 10), HORIZONTAL_CENTER);
	r.btn_gray = new_button(p_pos, new_color(101, 101, 101),
		new_vector_4d(90, 5, 2, 17.5), HORIZONTAL_CENTER);
	r.btn_neg = new_button(p_pos, new_color(101, 101, 42),
		new_vector_4d(90, 5, 2, 25), HORIZONTAL_CENTER);
	r.btn_sepia = new_button(p_pos, new_color(102, 59, 42),
		new_vector_4d(90, 5, 2, 32.5), HORIZONTAL_CENTER);
	r.btn_cart = new_button(p_pos, new_color(0x42, 0x00, 0xc9),
		new_vector_4d(90, 5, 2, 40), HORIZONTAL_CENTER);
	r.opt = new_m_label("Tools :", new_color(0xff, 0xff, 0xff),
		new_vector_4d(96, 10, 2, 47.5), p_pos.w);
	r.btn_shot = new_button(p_pos, new_color(42, 0x101, 0x19),
		new_vector_4d(90, 5, 2, 55), HORIZONTAL_CENTER);
	return (r);
}

static void		set_titles(t_right r, t_vector4d btn_s, t_color white)
{
	set_title_btn(r.btn_def, "Default", btn_s, white);
	set_title_btn(r.btn_gray, "Black & White", btn_s, white);
	set_title_btn(r.btn_neg, "Negative", btn_s, white);
	set_title_btn(r.btn_sepia, "Sepia", btn_s, white);
	set_title_btn(r.btn_cart, "Cartoon", btn_s, white);
	set_title_btn(r.btn_shot, "ScreenShot", btn_s, white);
}

t_bloc			*create_bloc_filter(int w, int h)
{
	t_bloc		*bc;
	t_right		r;
	t_color		white;
	t_vector4d	btn_s;

	white = new_color(0xff, 0xff, 0xff);
	btn_s = new_vector_4d(101, 55, 0, 0);
	bc = new_bloc(new_vector_2d(w, h), new_color(0x00, 0x3a, 0x42),
		new_vector_4d(15, 96, 1.5f, 2), RIGHT_UP_CONER);
	set_title_bloc(bc, "Filters :", new_vector_4d(96, 10, 2, 2), white);
	init_lstobj(bc, 7);
	r = right_obj(bc->pos);
	set_titles(r, btn_s, white);
	bc->lst_obj[0] = new_obj(r.btn_def, sizeof(r.btn_def), BUTTON);
	bc->lst_obj[1] = new_obj(r.btn_gray, sizeof(r.btn_gray), BUTTON);
	bc->lst_obj[2] = new_obj(r.btn_neg, sizeof(r.btn_neg), BUTTON);
	bc->lst_obj[3] = new_obj(r.btn_sepia, sizeof(r.btn_sepia), BUTTON);
	bc->lst_obj[4] = new_obj(r.btn_cart, sizeof(r.btn_cart), BUTTON);
	bc->lst_obj[5] = new_obj(r.opt, sizeof(r.opt), LABEL);
	bc->lst_obj[6] = new_obj(r.btn_shot, sizeof(r.btn_shot), BUTTON);
	return (bc);
}
