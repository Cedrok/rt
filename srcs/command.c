/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cpieri <cpieri@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/22 10:01:24 by cpieri            #+#    #+#             */
/*   Updated: 2018/06/22 17:38:46 by cpieri           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

static int	m_value(int value, int c)
{
	value += (c == '+') ? 1 : -1;
	return (value);
}

void	on_move(void *p, int type)
{
	t_all		*param;
	t_button	*on;
	t_color		white;
	t_color		on_off;
	t_vector4d	btn_s;

	param = (t_all*)p;
	white = new_color(0xff, 0xff, 0xff);
	btn_s = new_vector_4d(101, 55, 0, 0);
	on = ((t_button*)param->ui.bc_lft->lst_obj[0]->obj);
	on->type = (type == 1) ? 0 : 1;
	if (type == 0)
	{
		on_off = new_color(0, 0x42, 0x19);
		on->color = on_off;
		set_title_btn(on, "Move Obj: ON", btn_s, white);
	}
	if (type == 1)
	{
		on_off = new_color(0x42, 0, 0x19);
		on->color = on_off;
		set_title_btn(on, "Move Obj: OFF", btn_s, white);
	}
	refresh_surf(param, param->data.filter);
}

static t_shape	*get_shape_with_id(int id, t_scene sc)
{
	t_shape	*shape;

	while (sc.shape_lst != NULL)
	{
		shape = (t_shape*)sc.shape_lst->content;
		if (shape->type == -1)
			break ;
		if (shape->id == id)
			break ;
		sc.shape_lst = sc.shape_lst->next;
	}
	return (shape);
}

void	move_shape(void *p, int type)
{
	t_all	*param;
	t_scene	sc;
	t_shape	*shape;
	int		is_move;

	param = (t_all*)p;
	is_move = ((t_button*)param->ui.bc_lft->lst_obj[0]->obj)->type;
	sc = param->scene;
	if (is_move == 1)
	{
		shape = get_shape_with_id(param->ui.g_id, sc);
		if (type == 0 || type == 1)
			shape->origin.y = (type == 1) ? m_value(shape->origin.y, '-') : m_value(shape->origin.y, '+');
		if (type == 2 || type == 4)
			shape->origin.x = (type == 2) ? m_value(shape->origin.x, '-') : m_value(shape->origin.x, '+');
		if (type == 3 || type == 5)
			shape->origin.z = (type == 5) ? m_value(shape->origin.z, '-') : m_value(shape->origin.z, '+');
		refresh_img(param);
	}
}

int		rot_value(t_shape *shape, int value, char c)
{
	t_mat3d		mat;
	double		modif;

	modif = 5;
	if (value == 0 || value == 1)
		(c == '+') ? rotate_z(&mat, modif) : rotate_z(&mat, -modif);
	if (value == 2 || value == 3)
		(c == '+') ? rotate_x(&mat, modif) : rotate_x(&mat, -modif);
	if (value == 4 || value == 5)
		(c == '+') ? rotate_z(&mat, modif) : rotate_z(&mat, -modif);
	shape->rot = matrix_mult(shape->rot, mat);
	shape->inv_rot = matrix_inv(shape->rot);
	return (1);
}


void	rot_shape(void *p, int type)
{
	t_all	*param;
	t_scene	sc;
	t_shape	*shape;
	int		is_move;

	param = (t_all*)p;
	is_move = ((t_button*)param->ui.bc_lft->lst_obj[0]->obj)->type;
	sc = param->scene;
	if (is_move == 1)
	{
		shape = get_shape_with_id(param->ui.g_id, sc);
		if (type == 0 || type == 2 || type == 4)
			rot_value(shape, type, '+');
		else
			rot_value(shape, type, '-');
		refresh_img(param);
	}
}
