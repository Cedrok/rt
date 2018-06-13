/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   inputs.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cpieri <cpieri@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/06 12:36:24 by tmilon            #+#    #+#             */
/*   Updated: 2018/06/13 17:15:51 by cvautrai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"
#include <stdlib.h>

static void		move_offset(double *offset, char c)
{
	*offset += (c == '+') ? 0.1f : -0.1f;
}

static int		set_fastmode(int *fast)
{
	*fast *= -1;
	return (1);
}

static int		translation(t_all *param, int key)
{
	t_vector3d	*org;

	org = &param->scene.camera.origin;
	if (key == SDLK_RIGHT)
		move_offset(&org->x, '+');
	else if (key == SDLK_LEFT)
		move_offset(&org->x, '-');
	else if (key == SDLK_PAGEUP)
		move_offset(&org->y, '+');
	else if (key == SDLK_PAGEDOWN)
		move_offset(&org->y, '-');
	else if (key == SDLK_DOWN)
		move_offset(&org->z, '-');
	else if (key == SDLK_UP)
		move_offset(&org->z, '+');
	return (1);
}

static void		refresh_surf(t_all *param)
{
	param->data.filter = (param->data.filter < 4) ? param->data.filter + 1 : 0;
	clear_render(param->env);
	new_ui(param);
	put_filter(*param);
	param->env->rend = surface_2_rend(param->env);
}

int				sdl_key(t_all *param, int key)
{
	int			valid_key;

	valid_key = 0;
	if (key == SDLK_ESCAPE)
		quit_exe(*param);
	if (key == SDLK_RIGHT || key == SDLK_LEFT || key == SDLK_UP
			|| key == SDLK_DOWN || key == SDLK_PAGEUP || key == SDLK_PAGEDOWN)
		valid_key = translation(param, key);
	else if (key == SDLK_q || key == SDLK_w || key == SDLK_e || key == SDLK_a
			|| key == SDLK_s || key == SDLK_d)
		valid_key = rotate_event(param, key);
	else if (key == SDLK_r)
		valid_key = set_fastmode(&param->data.fastmode);
	else if (key == SDLK_c)
		refresh_surf(param);
	if (valid_key)
		refresh_img(param);
	return (0);
}
