/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   setf_btn.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cpieri <cpieri@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/15 09:57:39 by bocal             #+#    #+#             */
/*   Updated: 2018/06/24 16:56:32 by cpieri           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

void	setf_btn_r(t_bloc *bc, t_all *param)
{
	t_right		r;

	param = NULL;
	r.btn_def = ((t_button*)bc->lst_obj[0]->obj);
	r.btn_gray = ((t_button*)bc->lst_obj[1]->obj);
	r.btn_neg = ((t_button*)bc->lst_obj[2]->obj);
	r.btn_sepia = ((t_button*)bc->lst_obj[3]->obj);
	r.btn_cart = ((t_button*)bc->lst_obj[4]->obj);
	r.btn_alias = ((t_button*)bc->lst_obj[5]->obj);
	r.btn_shot = ((t_button*)bc->lst_obj[7]->obj);
	r.btn_fst = ((t_button*)bc->lst_obj[8]->obj);
	r.btn_sc1 = ((t_button*)bc->lst_obj[9]->obj);
	r.btn_sc2 = ((t_button*)bc->lst_obj[10]->obj);
	r.btn_sc3 = ((t_button*)bc->lst_obj[11]->obj);
	set_btn_callback(r.btn_def, &cartoon_mode, NULL, 5);
	set_btn_callback(r.btn_sepia, &refresh_surf, NULL, 0);
	set_btn_callback(r.btn_gray, &refresh_surf, NULL, 2);
	set_btn_callback(r.btn_neg, &refresh_surf, NULL, 1);
	set_btn_callback(r.btn_cart, &cartoon_mode, NULL, 4);
	set_btn_callback(r.btn_alias, &refresh_surf, NULL, 3);
	set_btn_callback(r.btn_shot, &screenshot, NULL, 0);
	set_btn_callback(r.btn_fst, &btn_fastmode, NULL, 0);
	set_btn_callback(r.btn_sc1, &change_scene, NULL, SDLK_1);
	set_btn_callback(r.btn_sc2, &change_scene, NULL, SDLK_2);
	set_btn_callback(r.btn_sc3, &change_scene, NULL, SDLK_3);
}

void	setf_btn_c(t_bloc *bc, t_all *param)
{
	t_center	c;

	param = NULL;
	c.btn_sph = ((t_button*)bc->lst_obj[0]->obj);
	c.btn_cyl = ((t_button*)bc->lst_obj[1]->obj);
	c.btn_pla = ((t_button*)bc->lst_obj[2]->obj);
	c.btn_cne = ((t_button*)bc->lst_obj[3]->obj);
	c.btn_lgt = ((t_button*)bc->lst_obj[4]->obj);
	set_btn_callback(c.btn_sph, &new_shape, NULL, SPHERE);
	set_btn_callback(c.btn_cyl, &new_shape, NULL, CYLINDER);
	set_btn_callback(c.btn_pla, &new_shape, NULL, PLANE);
	set_btn_callback(c.btn_cne, &new_shape, NULL, CONE);
	set_btn_callback(c.btn_lgt, &new_spot, NULL, 0);
}

static t_left	get_left_btn(t_bloc *bc)
{
	t_left	l;

	l.b_bool = ((t_button*)bc->lst_obj[0]->obj);
	l.mv_0 = ((t_button*)bc->lst_obj[1]->obj);
	l.mv_1 = ((t_button*)bc->lst_obj[2]->obj);
	l.mv_2 = ((t_button*)bc->lst_obj[3]->obj);
	l.mv_3 = ((t_button*)bc->lst_obj[4]->obj);
	l.mv_4 = ((t_button*)bc->lst_obj[5]->obj);
	l.mv_5 = ((t_button*)bc->lst_obj[6]->obj);
	l.rot_0 = ((t_button*)bc->lst_obj[7]->obj);
	l.rot_1 = ((t_button*)bc->lst_obj[8]->obj);
	l.rot_2 = ((t_button*)bc->lst_obj[9]->obj);
	l.rot_3 = ((t_button*)bc->lst_obj[10]->obj);
	l.rot_4 = ((t_button*)bc->lst_obj[11]->obj);
	l.rot_5 = ((t_button*)bc->lst_obj[12]->obj);
	l.dsel = ((t_button*)bc->lst_obj[13]->obj);
	l.del = ((t_button*)bc->lst_obj[14]->obj);
	return (l);
}

void	setf_btn_l(t_bloc *bc, t_all *param)
{
	t_left	l;

	param = NULL;
	l = get_left_btn(bc);
	set_btn_callback(l.b_bool, &on_move, NULL, 0);
	set_btn_callback(l.mv_0, &move_shape, NULL, 0);
	set_btn_callback(l.mv_1, &move_shape, NULL, 1);
	set_btn_callback(l.mv_2, &move_shape, NULL, 2);
	set_btn_callback(l.mv_3, &move_shape, NULL, 3);
	set_btn_callback(l.mv_4, &move_shape, NULL, 4);
	set_btn_callback(l.mv_5, &move_shape, NULL, 5);
	set_btn_callback(l.rot_0, &rot_shape, NULL, 0);
	set_btn_callback(l.rot_1, &rot_shape, NULL, 1);
	set_btn_callback(l.rot_2, &rot_shape, NULL, 2);
	set_btn_callback(l.rot_3, &rot_shape, NULL, 3);
	set_btn_callback(l.rot_4, &rot_shape, NULL, 4);
	set_btn_callback(l.rot_5, &rot_shape, NULL, 5);
	set_btn_callback(l.dsel, &dselect, NULL, 0);
	set_btn_callback(l.del, &del_shape, NULL, 0);
}
