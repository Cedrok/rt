/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ui_command.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cpieri <cpieri@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/22 12:03:22 by cpieri            #+#    #+#             */
/*   Updated: 2018/06/22 14:18:55 by cpieri           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

static t_left	left_obj(t_vector4d p_pos)
{
	t_left		l;
	t_color		brun;

	brun = new_color(101, 0x42, 0);
	l.b_bool = new_button(p_pos, new_color(0x42, 0, 0x19),
		new_vector_4d(90, 5, 2, 10), HORIZONTAL_CENTER);
	l.rot_0 = new_button(p_pos, brun, new_vector_4d(19, 5, 0, 34.5),
		HORIZONTAL_CENTER);
	l.rot_1 = new_button(p_pos, brun, new_vector_4d(19, 5, 0, 42),
		HORIZONTAL_CENTER);
	l.rot_2 = new_button(p_pos, brun, new_vector_4d(19, 5, 12, 42),
		LEFT_UP_CONER);
	l.rot_3 = new_button(p_pos, brun, new_vector_4d(19, 5, 2, 42),
		RIGHT_UP_CONER);
	l.rot_4 = new_button(p_pos, brun, new_vector_4d(19, 5, 12, 34.5),
		LEFT_UP_CONER);
	l.rot_5 = new_button(p_pos, brun, new_vector_4d(19, 5, 2, 34.5),
		RIGHT_UP_CONER);
	return (l);
}

static t_left	left_obj1(t_vector4d p_pos, t_left l)
{
	t_color		brun;

	brun = new_color(101, 0x42, 0);
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
	return (l);
}

static void		ladd_2_lst(t_bloc *bc, t_left l)
{
	bc->lst_obj[0] = new_obj(l.b_bool, sizeof(l.b_bool), BUTTON);
	bc->lst_obj[1] = new_obj(l.mv_0, sizeof(l.mv_0), BUTTON);
	bc->lst_obj[2] = new_obj(l.mv_1, sizeof(l.mv_1), BUTTON);
	bc->lst_obj[3] = new_obj(l.mv_2, sizeof(l.mv_2), BUTTON);
	bc->lst_obj[4] = new_obj(l.mv_3, sizeof(l.mv_3), BUTTON);
	bc->lst_obj[5] = new_obj(l.mv_4, sizeof(l.mv_4), BUTTON);
	bc->lst_obj[6] = new_obj(l.mv_5, sizeof(l.mv_5), BUTTON);
	bc->lst_obj[7] = new_obj(l.rot_0, sizeof(l.rot_0), BUTTON);
	bc->lst_obj[8] = new_obj(l.rot_1, sizeof(l.rot_1), BUTTON);
	bc->lst_obj[9] = new_obj(l.rot_2, sizeof(l.rot_2), BUTTON);
	bc->lst_obj[10] = new_obj(l.rot_3, sizeof(l.rot_3), BUTTON);
	bc->lst_obj[11] = new_obj(l.rot_4, sizeof(l.rot_4), BUTTON);
	bc->lst_obj[12] = new_obj(l.rot_5, sizeof(l.rot_5), BUTTON);
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
	set_title_bloc(bc, "Commands :", new_vector_4d(96, 10, 2, 2),
		new_color(255, 255, 255));
	init_lstobj(bc, 13);
	l = left_obj(bc->pos);
	l = left_obj1(bc->pos, l);
	set_title_btn(l.b_bool, "Move Obj: OFF", btn_s, white);
	ladd_2_lst(bc, l);
	return (bc);
}