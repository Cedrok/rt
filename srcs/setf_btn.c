/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   setf_btn.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clementpieri <clementpieri@student.42.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/15 09:57:39 by bocal             #+#    #+#             */
/*   Updated: 2018/06/17 16:34:58 by clementpier      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"
// set_btn_callback(btn, void(*f)(void*), void *param)

void    setf_btn_r(t_bloc *bc, t_all *param)
{
    t_right     r;

    r.btn_def = ((t_button*)bc->lst_obj[0]->obj);
    r.btn_gray = ((t_button*)bc->lst_obj[1]->obj);
    r.btn_neg = ((t_button*)bc->lst_obj[2]->obj);
    r.btn_sepia = ((t_button*)bc->lst_obj[3]->obj);
    r.btn_shot = ((t_button*)bc->lst_obj[5]->obj);
    set_btn_callback(r.btn_sepia, &refresh_surf, param, 0);
    set_btn_callback(r.btn_gray, &refresh_surf, param, 2);
    set_btn_callback(r.btn_neg, &refresh_surf, param, 1);
    set_btn_callback(r.btn_def, &refresh_surf, param, 4);
    set_btn_callback(r.btn_shot, &screenshot, param, 0);
}

void    setf_btn_c(t_bloc *bc, t_all *param)
{
    t_button	*btn_sph;
	t_button	*btn_cyl;
	t_button	*btn_pla;
	t_button	*btn_cne;
	t_button	*btn_lgt;

    btn_sph = ((t_button*)bc->lst_obj[0]->obj);
	btn_cyl = ((t_button*)bc->lst_obj[1]->obj);
	btn_pla = ((t_button*)bc->lst_obj[2]->obj);
	btn_cne = ((t_button*)bc->lst_obj[3]->obj);
	btn_lgt = ((t_button*)bc->lst_obj[4]->obj);
    set_btn_callback(btn_sph, &new_shape, param, SPHERE);
    set_btn_callback(btn_cyl, &new_shape, param, CYLINDER);
    set_btn_callback(btn_pla, &new_shape, param, PLANE);
    set_btn_callback(btn_cne, &new_shape, param, CONE);
    set_btn_callback(btn_lgt, &new_spot, param, 0);
}