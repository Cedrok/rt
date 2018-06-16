/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ui.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clementpieri <clementpieri@student.42.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/30 11:06:00 by cpieri            #+#    #+#             */
/*   Updated: 2018/06/16 19:27:49 by clementpier      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

static t_bloc		*create_bloc_center(int w, int h)
{
	t_bloc		*bc;
	t_button	*btn_sph;
	t_button	*btn_cyl;
	t_button	*btn_pla;
	t_button	*btn_cne;
	t_button	*btn_lgt;

	bc = new_bloc(new_vector_2d(w, h), new_color(0x00, 0x3a, 0x42), new_vector_4d(63, 10, 1.5f, 2), HORIZONTAL_CENTER);
	set_title_bloc(bc, "Ajouter des objets :", new_vector_4d(96, 70, 2, 5), new_color(255, 255, 255));
	init_lstobj(bc, 5);
	btn_sph = new_button(bc->pos, new_color(0, 0x42, 101), new_vector_4d(3.5, 38, 37.5, -3), LEFT_DOWN_CONER);
	btn_cyl = new_button(bc->pos, new_color(0, 0x42, 101), new_vector_4d(3.5, 38, 42.5, -3), LEFT_DOWN_CONER);
	btn_pla = new_button(bc->pos, new_color(0, 0x42, 101), new_vector_4d(3.5, 38, 47.5, -3), LEFT_DOWN_CONER);
	btn_cne = new_button(bc->pos, new_color(0, 0x42, 101), new_vector_4d(3.5, 38, 52.5, -3), LEFT_DOWN_CONER);
	btn_lgt = new_button(bc->pos, new_color(0, 0x42, 101), new_vector_4d(3.5, 38, 57.5, -3), LEFT_DOWN_CONER);
	bc->lst_obj[0] = new_obj(btn_sph, sizeof(btn_sph), BUTTON);
	bc->lst_obj[1] = new_obj(btn_cyl, sizeof(btn_cyl), BUTTON);
	bc->lst_obj[2] = new_obj(btn_pla, sizeof(btn_pla), BUTTON);
	bc->lst_obj[3] = new_obj(btn_cne, sizeof(btn_cne), BUTTON);
	bc->lst_obj[4] = new_obj(btn_lgt, sizeof(btn_lgt), BUTTON);
	return (bc);
}

static t_bloc		*create_bloc_filter(int w, int h)
{
	t_bloc		*bc;
	t_button	*btn_sepia;
	t_button	*btn_gray;
	t_button	*btn_neg;
	t_button	*btn_def;
	t_button	*btn_shot;

	bc = new_bloc(new_vector_2d(w, h), new_color(0x00, 0x3a, 0x42), new_vector_4d(15, 96, 1.5f, 2), RIGHT_UP_CONER);
	set_title_bloc(bc, "Les Options :", new_vector_4d(96, 10, 2, 5), new_color(255, 255, 255));
	init_lstobj(bc, 5);
	btn_sepia = new_button(bc->pos, new_color(102, 59, 42), new_vector_4d(90, 5, 2, 10), HORIZONTAL_CENTER);
	btn_gray = new_button(bc->pos, new_color(101, 101, 101), new_vector_4d(90, 5, 2, 17.5), HORIZONTAL_CENTER);
	btn_neg = new_button(bc->pos, new_color(101, 101, 42), new_vector_4d(90, 5, 2, 25), HORIZONTAL_CENTER);
	btn_def = new_button(bc->pos, new_color(42, 101, 0x19), new_vector_4d(90, 5, 2, 32.5), HORIZONTAL_CENTER);
	btn_shot = new_button(bc->pos, new_color(42, 0x101, 0x19), new_vector_4d(90, 5, 2, 40), HORIZONTAL_CENTER);
	set_title_btn(btn_sepia, "Sepia", new_vector_4d(101, 55, 0, 0), new_color(255, 255, 255));
	set_title_btn(btn_gray, "Black & White", new_vector_4d(101, 55, 0, 0), new_color(255, 255, 255));
	set_title_btn(btn_neg, "Negative", new_vector_4d(101, 55, 0, 0), new_color(255, 255, 255));
	set_title_btn(btn_def, "Default", new_vector_4d(101, 55, 0, 0), new_color(255, 255, 255));
	set_title_btn(btn_shot, "ScreenShot", new_vector_4d(101, 55, 0, 0), new_color(255, 255, 255));
	bc->lst_obj[0] = new_obj(btn_sepia, sizeof(btn_sepia), BUTTON);
	bc->lst_obj[1] = new_obj(btn_gray, sizeof(btn_gray), BUTTON);
	bc->lst_obj[2] = new_obj(btn_neg, sizeof(btn_neg), BUTTON);
	bc->lst_obj[3] = new_obj(btn_def, sizeof(btn_def), BUTTON);
	bc->lst_obj[4] = new_obj(btn_shot, sizeof(btn_shot), BUTTON);
	return (bc);
}

static t_bloc		*create_bloc_left(int w, int h)
{
	t_bloc		*bc;
	t_button	*btn_up;
	t_button	*btn_down;
	t_button	*btn_rght;
	t_button	*btn_lft;

	bc = new_bloc(new_vector_2d(w, h), new_color(0x00, 0x3a, 0x42), new_vector_4d(15, 96, 1.5f, 2), LEFT_UP_CONER);
	set_title_bloc(bc, "Commandes :", new_vector_4d(96, 10, 2, 5), new_color(255, 255, 255));
	init_lstobj(bc, 4);
	btn_up = new_button(bc->pos, new_color(101, 0x42, 0), new_vector_4d(19, 5, 0, 10), HORIZONTAL_CENTER);
	btn_down = new_button(bc->pos, new_color(101, 0x42, 0), new_vector_4d(19, 5, 0, 17.5), HORIZONTAL_CENTER);
	btn_rght = new_button(bc->pos, new_color(101, 0x42, 0), new_vector_4d(19, 5, 2, 17.5), RIGHT_UP_CONER);
	btn_lft = new_button(bc->pos, new_color(101, 0x42, 0), new_vector_4d(19, 5, 12, 17.5), LEFT_UP_CONER);
	bc->lst_obj[0] = new_obj(btn_up, sizeof(btn_up), BUTTON);
	bc->lst_obj[1] = new_obj(btn_down, sizeof(btn_down), BUTTON);
	bc->lst_obj[2] = new_obj(btn_rght, sizeof(btn_rght), BUTTON);
	bc->lst_obj[3] = new_obj(btn_lft, sizeof(btn_lft), BUTTON);
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
