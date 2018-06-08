/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ui.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cpieri <cpieri@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/30 11:06:00 by cpieri            #+#    #+#             */
/*   Updated: 2018/06/07 19:08:22 by cpieri           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

static t_bloc		create_bloc_center(t_all *param)
{
	t_bloc		bloc;
	t_button	btn_sph;
	t_button	btn_cyl;
	t_button	btn_pla;
	t_button	btn_cne;
	t_button	btn_lgt;

	bloc = new_bloc(new_vector_2d(param->env->w, param->env->h), new_color(0x00, 0x3a, 0x42), new_vector_4d(63, 10, 1.5f, 2), HORIZONTAL_CENTER);
	set_title_bloc(&bloc, "Ajouter des objets :", new_vector_4d(96, 70, 2, 5), new_color(255, 255, 255));
	if (!(bloc.lst_obj = (t_obj*)malloc(sizeof(t_obj) * 6)))
		return (bloc);
	btn_sph = new_button(bloc.pos, new_color(42, 101, 19), new_vector_4d(3.5, 38, 35, -3), LEFT_DOWN_CONER);
	btn_cyl = new_button(bloc.pos, new_color(42, 101, 19), new_vector_4d(3.5, 38, 40, -3), LEFT_DOWN_CONER);
	btn_pla = new_button(bloc.pos, new_color(42, 101, 19), new_vector_4d(3.5, 38, 45, -3), LEFT_DOWN_CONER);
	btn_cne = new_button(bloc.pos, new_color(42, 101, 19), new_vector_4d(3.5, 38, 50, -3), LEFT_DOWN_CONER);
	btn_lgt = new_button(bloc.pos, new_color(42, 101, 19), new_vector_4d(3.5, 38, 55, -3), LEFT_DOWN_CONER);
	//set_title_btn(&btn_sph, "Sphere", new_vector_4d(0, 30, 0, 0), new_color(255, 255, 255));
	bloc.lst_obj[0] = new_obj(&btn_sph, sizeof(btn_sph), BUTTON);
	bloc.lst_obj[1] = new_obj(&btn_cyl, sizeof(btn_cyl), BUTTON);
	bloc.lst_obj[2] = new_obj(&btn_pla, sizeof(btn_pla), BUTTON);
	bloc.lst_obj[3] = new_obj(&btn_cne, sizeof(btn_cne), BUTTON);
	bloc.lst_obj[4] = new_obj(&btn_lgt, sizeof(btn_lgt), BUTTON);
	bloc.lst_obj[5] = new_obj(NULL, 0, 0);
	return (bloc);
}

static t_bloc		create_bloc_filter(t_all *param)
{
	t_bloc		bloc;
	t_button	btn_sepia;
	t_button	btn_gray;
	t_button	btn_neg;
	t_button	btn;

	bloc = new_bloc(new_vector_2d(param->env->w, param->env->h), new_color(0x00, 0x3a, 0x42), new_vector_4d(15, 96, 1.5f, 2), RIGHT_UP_CONER);
	set_title_bloc(&bloc, "Les Filtres :", new_vector_4d(96, 10, 2, 5), new_color(255, 255, 255));
	if (!(bloc.lst_obj = (t_obj*)malloc(sizeof(t_obj) * 4)))
		return (bloc);
	btn_sepia = new_button(bloc.pos, new_color(102, 59, 42), new_vector_4d(90, 5, 2, 10), HORIZONTAL_CENTER);
	set_title_btn(&btn_sepia, "Sepia", new_vector_4d(101, 55, 0, 0), new_color(255, 255, 255));
	btn_gray = new_button(bloc.pos, new_color(101, 101, 101), new_vector_4d(90, 5, 2, 17.5), HORIZONTAL_CENTER);
	set_title_btn(&btn_gray, "Black & White", new_vector_4d(101, 55, 0, 0), new_color(255, 255, 255));
	btn_neg = new_button(bloc.pos, new_color(101, 101, 42), new_vector_4d(90, 5, 2, 25), HORIZONTAL_CENTER);
	set_title_btn(&btn_neg, "Negative", new_vector_4d(101, 55, 0, 0), new_color(255, 255, 255));
	btn = new_button(bloc.pos, new_color(101, 101, 42), new_vector_4d(90, 5, 2, 35), HORIZONTAL_CENTER);
	bloc.lst_obj[0] = new_obj(&btn_sepia, sizeof(btn_sepia), BUTTON);
	bloc.lst_obj[1] = new_obj(&btn_gray, sizeof(btn_gray), BUTTON);
	bloc.lst_obj[2] = new_obj(&btn_neg, sizeof(btn_neg), BUTTON);
	bloc.lst_obj[3] = new_obj(NULL, 0, 0);
	return (bloc);
}

int	    	new_ui(t_all *param)
{
	t_bloc		bloc_2;

	draw_bloc(create_bloc_filter(param), param->env->rend);
	draw_bloc(create_bloc_center(param), param->env->rend);
	bloc_2 = new_bloc(new_vector_2d(param->env->w, param->env->h), new_color(0x00, 0x3a, 0x42), new_vector_4d(15, 96, 1.5f, 2), LEFT_UP_CONER);
	draw_fill_render(bloc_2.pos, bloc_2.color, param->env->rend);
	return (0);
}
