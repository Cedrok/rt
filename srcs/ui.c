/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ui.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cpieri <cpieri@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/30 11:06:00 by cpieri            #+#    #+#             */
/*   Updated: 2018/06/20 11:17:59 by cpieri           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

static t_bloc		*create_bloc_center(int w, int h)
{
	t_bloc		*bc;
	t_center	c;
	t_color		blue;
	int			p;

	blue = new_color(0, 0x42, 101);
	p = LEFT_DOWN_CONER;
	bc = new_bloc(new_vector_2d(w, h), new_color(0x00, 0x3a, 0x42),
		new_vector_4d(63, 10, 1.5f, 2), HORIZONTAL_CENTER);
	set_title_bloc(bc, "Add Objects :", new_vector_4d(96, 70, 2, 2),
		new_color(255, 255, 255));
	init_lstobj(bc, 5);
	c.btn_sph = new_button(bc->pos, blue, new_vector_4d(3.5, 38, 37.5, -3), p);
	c.btn_cyl = new_button(bc->pos, blue, new_vector_4d(3.5, 38, 42.5, -3), p);
	c.btn_pla = new_button(bc->pos, blue, new_vector_4d(3.5, 38, 47.5, -3), p);
	c.btn_cne = new_button(bc->pos, blue, new_vector_4d(3.5, 38, 52.5, -3), p);
	c.btn_lgt = new_button(bc->pos, blue, new_vector_4d(3.5, 38, 57.5, -3), p);
	bc->lst_obj[0] = new_obj(c.btn_sph, sizeof(c.btn_sph), BUTTON);
	bc->lst_obj[1] = new_obj(c.btn_cyl, sizeof(c.btn_cyl), BUTTON);
	bc->lst_obj[2] = new_obj(c.btn_pla, sizeof(c.btn_pla), BUTTON);
	bc->lst_obj[3] = new_obj(c.btn_cne, sizeof(c.btn_cne), BUTTON);
	bc->lst_obj[4] = new_obj(c.btn_lgt, sizeof(c.btn_lgt), BUTTON);
	return (bc);
}

static t_right		right_obj(t_vector4d p_pos)
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

static t_bloc		*create_bloc_filter(int w, int h)
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
	set_title_btn(r.btn_def, "Default", btn_s, white);
	set_title_btn(r.btn_gray, "Black & White", btn_s, white);
	set_title_btn(r.btn_neg, "Negative", btn_s, white);
	set_title_btn(r.btn_sepia, "Sepia", btn_s, white);
	set_title_btn(r.btn_cart, "Cartoon", btn_s, white);
	set_title_btn(r.btn_shot, "ScreenShot", btn_s, white);
	bc->lst_obj[0] = new_obj(r.btn_def, sizeof(r.btn_def), BUTTON);
	bc->lst_obj[1] = new_obj(r.btn_gray, sizeof(r.btn_gray), BUTTON);
	bc->lst_obj[2] = new_obj(r.btn_neg, sizeof(r.btn_neg), BUTTON);
	bc->lst_obj[3] = new_obj(r.btn_sepia, sizeof(r.btn_sepia), BUTTON);
	bc->lst_obj[4] = new_obj(r.btn_cart, sizeof(r.btn_cart), BUTTON);
	bc->lst_obj[5] = new_obj(r.opt, sizeof(r.opt), LABEL);
	bc->lst_obj[6] = new_obj(r.btn_shot, sizeof(r.btn_shot), BUTTON);
	return (bc);
}

static t_bloc		*create_bloc_left(int w, int h)
{
	t_bloc		*bc;
	t_left		l;
	t_color		brun;

	brun = new_color(101, 0x42, 0);
	bc = new_bloc(new_vector_2d(w, h), new_color(0x00, 0x3a, 0x42),
		new_vector_4d(15, 96, 1.5f, 2), LEFT_UP_CONER);
	set_title_bloc(bc, "Commands :", new_vector_4d(96, 10, 2, 2),
		new_color(255, 255, 255));
	init_lstobj(bc, 4);
	l.btn_up = new_button(bc->pos, brun, new_vector_4d(19, 5, 0, 10),
		HORIZONTAL_CENTER);
	l.btn_down = new_button(bc->pos, brun, new_vector_4d(19, 5, 0, 17.5),
		HORIZONTAL_CENTER);
	l.btn_rght = new_button(bc->pos, brun, new_vector_4d(19, 5, 2, 17.5),
		RIGHT_UP_CONER);
	l.btn_lft = new_button(bc->pos, brun, new_vector_4d(19, 5, 12, 17.5),
		LEFT_UP_CONER);
	bc->lst_obj[0] = new_obj(l.btn_up, sizeof(l.btn_up), BUTTON);
	bc->lst_obj[1] = new_obj(l.btn_down, sizeof(l.btn_down), BUTTON);
	bc->lst_obj[2] = new_obj(l.btn_rght, sizeof(l.btn_rght), BUTTON);
	bc->lst_obj[3] = new_obj(l.btn_lft, sizeof(l.btn_lft), BUTTON);
	return (bc);
}

int	    	new_ui(t_all *param)
{
	t_bloc	*bc_right;
	t_bloc	*bc_center;
	t_bloc	*bc_left;

	bc_right = create_bloc_filter(param->env->w, param->env->h);
	bc_center = create_bloc_center(param->env->w, param->env->h);
	bc_left = create_bloc_left(param->env->w, param->env->h);
	setf_btn_r(bc_right, param);
	setf_btn_c(bc_center, param);
	param->ui.bc_rght = bc_right;
	param->ui.bc_center = bc_center;
	param->ui.bc_lft = bc_left;
	return (0);
}
