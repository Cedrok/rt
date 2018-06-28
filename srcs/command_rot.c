/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command_rot.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cpieri <cpieri@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/22 18:15:21 by cpieri            #+#    #+#             */
/*   Updated: 2018/06/28 14:34:50 by cvautrai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

int				rot_value(t_shape *shape, int value, char c)
{
	t_mat3d		mat;
	double		modif;

	modif = 5;
	if (value == 2 || value == 3)
		(c == '+') ? rotate_z(&mat, modif) : rotate_z(&mat, -modif);
	if (value == 0 || value == 1)
		(c == '+') ? rotate_x(&mat, modif) : rotate_x(&mat, -modif);
	if (value == 4 || value == 5)
		(c == '+') ? rotate_y(&mat, modif) : rotate_y(&mat, -modif);
	shape->rot = matrix_mult(shape->rot, mat);
	shape->inv_rot = matrix_inv(shape->rot);
	return (1);
}

void			rot_shape(void *p, int type)
{
	t_all	*param;
	t_scene	sc;
	t_shape	*shape;

	param = (t_all*)p;
	sc = param->scene;
	shape = get_shape_with_id(param->ui.g_id, sc);
	if (type == 1 || type == 3 || type == 4)
		rot_value(shape, type, '+');
	else
		rot_value(shape, type, '-');
	refresh_img(param);
}

static void		check_first(t_list **lst, int id)
{
	t_shape	*shape;
	t_list	*tmp;

	shape = (t_shape*)(*lst)->content;
	if (shape->id == id)
	{
		tmp = *lst;
		(*lst) = (*lst)->next;
		tmp->next = NULL;
		ft_lstdelone(&tmp, &delshape_func);
	}
}

void			del_shape(void *p, int type)
{
	t_all	*param;
	t_shape	*shape;
	t_list	*lst;
	t_list	*tmp;

	param = (t_all*)p;
	(void)type;
	check_first(&param->scene.shape_lst, param->ui.g_id);
	lst = param->scene.shape_lst;
	while (lst != NULL)
	{
		if (lst->next != NULL)
			shape = (t_shape*)lst->next->content;
		if (shape->id == -1 || lst->next == NULL)
			break ;
		if (shape->id == param->ui.g_id)
		{
			tmp = lst->next;
			lst->next = lst->next->next;
			ft_lstdelone(&tmp, &delshape_func);
		}
		lst = lst->next;
	}
	refresh_img(param);
}

void			dselect(void *p, int type)
{
	t_all	*param;
	t_shape *shape;
	t_list	*head;

	(void)type;
	param = (t_all*)p;
	head = param->scene.shape_lst;
	while (param->scene.shape_lst != NULL)
	{
		shape = (t_shape*)param->scene.shape_lst->content;
		if (shape->id == param->ui.g_id)
			shape->color = shape->base_color;
		param->scene.shape_lst = param->scene.shape_lst->next;
	}
	param->scene.shape_lst = head;
	param->ui.g_id = -1;
	refresh_img(param);
}
