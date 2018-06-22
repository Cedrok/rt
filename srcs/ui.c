/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ui.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cpieri <cpieri@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/30 11:06:00 by cpieri            #+#    #+#             */
/*   Updated: 2018/06/22 13:46:44 by cpieri           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

static t_bloc	*create_bloc_center(int w, int h)
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

int				new_ui(t_all *param)
{
	t_bloc	*bc_right;
	t_bloc	*bc_center;
	t_bloc	*bc_left;

	bc_right = create_bloc_filter(param->env->w, param->env->h);
	bc_center = create_bloc_center(param->env->w, param->env->h);
	bc_left = create_bloc_left(param->env->w, param->env->h);
	setf_btn_r(bc_right, param);
	setf_btn_c(bc_center, param);
	setf_btn_l(bc_left, param);
	param->ui.bc_rght = bc_right;
	param->ui.bc_center = bc_center;
	param->ui.bc_lft = bc_left;
	return (0);
}
