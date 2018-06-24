/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ui_filters.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cpieri <cpieri@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/21 11:52:05 by cvautrai          #+#    #+#             */
/*   Updated: 2018/06/24 14:32:57 by cpieri           ###   ########.fr       */
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
	r.btn_fst = new_button(p_pos, new_color(42, 0x101, 0x19),
		new_vector_4d(90, 5, 2, 62.5), HORIZONTAL_CENTER);
	r.btn_sc1 = new_button(p_pos, new_color(42, 0x101, 0x19),
		new_vector_4d(90, 5, 2, 70), HORIZONTAL_CENTER);
	r.btn_sc2 = new_button(p_pos, new_color(42, 0x101, 0x19),
		new_vector_4d(90, 5, 2, 77.5), HORIZONTAL_CENTER);
	r.btn_sc3 = new_button(p_pos, new_color(42, 0x101, 0x19),
		new_vector_4d(90, 5, 2, 85), HORIZONTAL_CENTER);
	return (r);
}

static void		set_titles(t_right r, t_vector4d btn_s, t_color white,
	t_vector2d win_s)
{
	set_title_btn(r.btn_def, "Default", btn_s, white);
	set_title_btn(r.btn_gray, "Black & White", btn_s, white);
	set_title_btn(r.btn_neg, "Negative", btn_s, white);
	set_title_btn(r.btn_sepia, "Sepia", btn_s, white);
	set_title_btn(r.btn_cart, "Cartoon", btn_s, white);
	set_title_btn(r.btn_shot, "ScreenShot", btn_s, white);
	set_title_btn(r.btn_fst, "Fast Mode", btn_s, white);
	set_title_btn(r.btn_sc1, "Scene 1", btn_s, white);
	set_title_btn(r.btn_sc2, "Scene 2", btn_s, white);
	set_title_btn(r.btn_sc3, "Scene 3", btn_s, white);
	change_btn_fs(win_s, r.btn_def, btn_s);
	change_btn_fs(win_s, r.btn_gray, btn_s);
	change_btn_fs(win_s, r.btn_neg, btn_s);
	change_btn_fs(win_s, r.btn_sepia, btn_s);
	change_btn_fs(win_s, r.btn_cart, btn_s);
	change_btn_fs(win_s, r.btn_shot, btn_s);
	change_btn_fs(win_s, r.btn_fst, btn_s);
	change_btn_fs(win_s, r.btn_sc1, btn_s);
	change_btn_fs(win_s, r.btn_sc2, btn_s);
	change_btn_fs(win_s, r.btn_sc3, btn_s);
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
	change_bc_fs(new_vector_2d(w, h), bc, new_vector_4d(96, 10, 2, 2));
	init_lstobj(bc, 11);
	r = right_obj(bc->pos);
	set_titles(r, btn_s, white, new_vector_2d(w, h));
	change_lb_fs(new_vector_2d(w, h), r.opt, bc);
	bc->lst_obj[0] = new_obj(r.btn_def, sizeof(r.btn_def), BUTTON);
	bc->lst_obj[1] = new_obj(r.btn_gray, sizeof(r.btn_gray), BUTTON);
	bc->lst_obj[2] = new_obj(r.btn_neg, sizeof(r.btn_neg), BUTTON);
	bc->lst_obj[3] = new_obj(r.btn_sepia, sizeof(r.btn_sepia), BUTTON);
	bc->lst_obj[4] = new_obj(r.btn_cart, sizeof(r.btn_cart), BUTTON);
	bc->lst_obj[5] = new_obj(r.opt, sizeof(r.opt), LABEL);
	bc->lst_obj[6] = new_obj(r.btn_shot, sizeof(r.btn_shot), BUTTON);
	bc->lst_obj[7] = new_obj(r.btn_fst, sizeof(r.btn_fst), BUTTON);
	bc->lst_obj[8] = new_obj(r.btn_sc1, sizeof(r.btn_sc1), BUTTON);
	bc->lst_obj[9] = new_obj(r.btn_sc2, sizeof(r.btn_sc2), BUTTON);
	bc->lst_obj[10] = new_obj(r.btn_sc3, sizeof(r.btn_sc3), BUTTON);
	return (bc);
}
