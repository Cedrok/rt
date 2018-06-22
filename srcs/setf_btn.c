/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   setf_btn.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cpieri <cpieri@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/15 09:57:39 by bocal             #+#    #+#             */
/*   Updated: 2018/06/22 13:54:06 by cvautrai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

/*
** set_btn_callback(btn, void(*f)(void*), void *param)
*/

void	setf_btn_r(t_bloc *bc, t_all *param)
{
	t_right		r;

	r.btn_def = ((t_button*)bc->lst_obj[0]->obj);
	r.btn_gray = ((t_button*)bc->lst_obj[1]->obj);
	r.btn_neg = ((t_button*)bc->lst_obj[2]->obj);
	r.btn_sepia = ((t_button*)bc->lst_obj[3]->obj);
	r.btn_cart = ((t_button*)bc->lst_obj[4]->obj);
	r.btn_shot = ((t_button*)bc->lst_obj[6]->obj);
	r.btn_sc1 = ((t_button*)bc->lst_obj[7]->obj);
	r.btn_sc2 = ((t_button*)bc->lst_obj[8]->obj);
	r.btn_sc3 = ((t_button*)bc->lst_obj[9]->obj);
	set_btn_callback(r.btn_def, &cartoon_mode, param, 4);
	set_btn_callback(r.btn_sepia, &refresh_surf, param, 0);
	set_btn_callback(r.btn_gray, &refresh_surf, param, 2);
	set_btn_callback(r.btn_neg, &refresh_surf, param, 1);
	set_btn_callback(r.btn_cart, &cartoon_mode, param, 3);
	set_btn_callback(r.btn_shot, &screenshot, param, 0);
	set_btn_callback(r.btn_sc1, &change_scene, param, SDLK_1);
	set_btn_callback(r.btn_sc2, &change_scene, param, SDLK_2);
	set_btn_callback(r.btn_sc3, &change_scene, param, SDLK_3);
}

void	setf_btn_c(t_bloc *bc, t_all *param)
{
	t_center	c;

	c.btn_sph = ((t_button*)bc->lst_obj[0]->obj);
	c.btn_cyl = ((t_button*)bc->lst_obj[1]->obj);
	c.btn_pla = ((t_button*)bc->lst_obj[2]->obj);
	c.btn_cne = ((t_button*)bc->lst_obj[3]->obj);
	c.btn_lgt = ((t_button*)bc->lst_obj[4]->obj);
	set_btn_callback(c.btn_sph, &new_shape, param, SPHERE);
	set_btn_callback(c.btn_cyl, &new_shape, param, CYLINDER);
	set_btn_callback(c.btn_pla, &new_shape, param, PLANE);
	set_btn_callback(c.btn_cne, &new_shape, param, CONE);
	set_btn_callback(c.btn_lgt, &new_spot, param, 0);
}

void	setf_btn_l(t_bloc *bc, t_all *param)
{
	t_left	l;

	l.b_bool = ((t_button*)bc->lst_obj[0]->obj);
	set_btn_callback(l.b_bool, &on_move, param, 0);
}
