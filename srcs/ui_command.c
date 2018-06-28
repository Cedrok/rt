/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ui_command.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cpieri <cpieri@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/22 12:03:22 by cpieri            #+#    #+#             */
/*   Updated: 2018/06/28 14:37:32 by cvautrai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

static void		set_lft_titles(t_left l, t_vector4d btn_s, t_color white,
	t_vector2d win_s)
{
	set_title_btn(l.rot_0, "X+", btn_s, white);
	set_title_btn(l.rot_1, "X-", btn_s, white);
	set_title_btn(l.rot_2, "Y+", btn_s, white);
	set_title_btn(l.rot_3, "Y-", btn_s, white);
	set_title_btn(l.rot_4, "Z+", btn_s, white);
	set_title_btn(l.rot_5, "Z-", btn_s, white);
	set_title_btn(l.mv_0, "Z+", btn_s, white);
	set_title_btn(l.mv_1, "Z-", btn_s, white);
	set_title_btn(l.mv_2, "X-", btn_s, white);
	set_title_btn(l.mv_3, "Y-", btn_s, white);
	set_title_btn(l.mv_4, "X+", btn_s, white);
	set_title_btn(l.mv_5, "Y+", btn_s, white);
	change_btn_fs(win_s, l.mv_0, btn_s);
	change_btn_fs(win_s, l.mv_1, btn_s);
	change_btn_fs(win_s, l.mv_2, btn_s);
	change_btn_fs(win_s, l.mv_3, btn_s);
	change_btn_fs(win_s, l.mv_4, btn_s);
	change_btn_fs(win_s, l.mv_5, btn_s);
	change_btn_fs(win_s, l.rot_0, btn_s);
	change_btn_fs(win_s, l.rot_1, btn_s);
	change_btn_fs(win_s, l.rot_2, btn_s);
	change_btn_fs(win_s, l.rot_3, btn_s);
	change_btn_fs(win_s, l.rot_4, btn_s);
	change_btn_fs(win_s, l.rot_5, btn_s);
}

static t_left	left_obj(t_vector4d p_pos)
{
	t_left		l;
	t_color		brun;

	brun = new_color(158, 158, 158);
	l.trot = new_m_label("Rotation :", new_color(0xff, 0xff, 0xff),
		new_vector_4d(96, 10, 2, 32.5), p_pos.w);
	l.rot_0 = new_button(p_pos, brun, new_vector_4d(15, 4.5, 0, 40),
		HORIZONTAL_CENTER);
	l.rot_1 = new_button(p_pos, brun, new_vector_4d(15, 4.5, 0, 47.5),
		HORIZONTAL_CENTER);
	l.rot_2 = new_button(p_pos, brun, new_vector_4d(15, 4.5, 12, 47.5),
		LEFT_UP_CONER);
	l.rot_3 = new_button(p_pos, brun, new_vector_4d(15, 4.5, 2, 47.5),
		RIGHT_UP_CONER);
	l.rot_4 = new_button(p_pos, brun, new_vector_4d(15, 4.5, 12, 40),
		LEFT_UP_CONER);
	l.rot_5 = new_button(p_pos, brun, new_vector_4d(15, 4.5, 2, 40),
		RIGHT_UP_CONER);
	return (l);
}

static t_left	left_obj1(t_vector4d p_pos, t_left l)
{
	t_color		brun;

	brun = new_color(158, 158, 158);
	l.tran = new_m_label("Translation :", new_color(0xff, 0xff, 0xff),
		new_vector_4d(96, 10, 2, 10), p_pos.w);
	l.mv_0 = new_button(p_pos, brun, new_vector_4d(15, 4.5, 31, 17.5),
		LEFT_UP_CONER);
	l.mv_2 = new_button(p_pos, brun, new_vector_4d(15, 4.5, 8, 25),
		LEFT_UP_CONER);
	l.mv_1 = new_button(p_pos, brun, new_vector_4d(15, 4.5, 31, 25),
		LEFT_UP_CONER);
	l.mv_4 = new_button(p_pos, brun, new_vector_4d(15, 4.5, 54, 25),
		LEFT_UP_CONER);
	l.mv_3 = new_button(p_pos, brun, new_vector_4d(15, 4.5, 77, 25),
		LEFT_UP_CONER);
	l.mv_5 = new_button(p_pos, brun, new_vector_4d(15, 4.5, 77, 17.5),
		LEFT_UP_CONER);
	l.dsel = new_button(p_pos, brun, new_vector_4d(90, 5, 2, 82.5),
		HORIZONTAL_CENTER);
	l.del = new_button(p_pos, new_color(0xcf, 0x00, 0x19),
		new_vector_4d(90, 5, 2, 90), HORIZONTAL_CENTER);
	return (l);
}

static void		ladd_2_lst(t_bloc *bc, t_left l)
{
	bc->lst_obj[0] = new_obj(l.mv_0, sizeof(l.mv_0), BUTTON);
	bc->lst_obj[1] = new_obj(l.mv_1, sizeof(l.mv_1), BUTTON);
	bc->lst_obj[2] = new_obj(l.mv_2, sizeof(l.mv_2), BUTTON);
	bc->lst_obj[3] = new_obj(l.mv_3, sizeof(l.mv_3), BUTTON);
	bc->lst_obj[4] = new_obj(l.mv_4, sizeof(l.mv_4), BUTTON);
	bc->lst_obj[5] = new_obj(l.mv_5, sizeof(l.mv_5), BUTTON);
	bc->lst_obj[6] = new_obj(l.rot_0, sizeof(l.rot_0), BUTTON);
	bc->lst_obj[7] = new_obj(l.rot_1, sizeof(l.rot_1), BUTTON);
	bc->lst_obj[8] = new_obj(l.rot_2, sizeof(l.rot_2), BUTTON);
	bc->lst_obj[9] = new_obj(l.rot_3, sizeof(l.rot_3), BUTTON);
	bc->lst_obj[10] = new_obj(l.rot_4, sizeof(l.rot_4), BUTTON);
	bc->lst_obj[11] = new_obj(l.rot_5, sizeof(l.rot_5), BUTTON);
	bc->lst_obj[12] = new_obj(l.dsel, sizeof(l.dsel), BUTTON);
	bc->lst_obj[13] = new_obj(l.del, sizeof(l.del), BUTTON);
	bc->lst_obj[14] = new_obj(l.trot, sizeof(l.trot), LABEL);
	bc->lst_obj[15] = new_obj(l.tran, sizeof(l.tran), LABEL);
}

t_bloc			*create_bloc_left(int w, int h)
{
	t_bloc		*bc;
	t_left		l;
	t_color		white;
	t_vector4d	btn_s;

	white = new_color(0xff, 0xff, 0xff);
	btn_s = new_vector_4d(101, 55, 0, 0);
	bc = new_bloc(new_vector_2d(w, h), new_color(0x00, 0x3a, 0x42),
		new_vector_4d(15, 96, 1.5f, 2), LEFT_UP_CONER);
	set_title_bloc(bc, "Modifications :", new_vector_4d(96, 10, 2, 2),
		new_color(255, 255, 255));
	change_bc_fs(new_vector_2d(w, h), bc, new_vector_4d(96, 10, 2, 2));
	init_lstobj(bc, 16);
	l = left_obj(bc->pos);
	l = left_obj1(bc->pos, l);
	set_title_btn(l.dsel, "Deselect Obj", btn_s, white);
	set_title_btn(l.del, "Delete Obj", btn_s, white);
	change_btn_fs(new_vector_2d(w, h), l.dsel, btn_s);
	change_btn_fs(new_vector_2d(w, h), l.del, btn_s);
	change_lb_fs(new_vector_2d(w, h), l.trot, bc);
	change_lb_fs(new_vector_2d(w, h), l.tran, bc);
	set_lft_titles(l, btn_s, white, new_vector_2d(w, h));
	ladd_2_lst(bc, l);
	color_btn_mv(bc);
	return (bc);
}
