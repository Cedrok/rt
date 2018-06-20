/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   inputs.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cpieri <cpieri@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/06 12:36:24 by tmilon            #+#    #+#             */
/*   Updated: 2018/06/20 17:42:49 by Pringles         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"
#include <stdlib.h>

static void	move_offset(double *offset, char c, double move)
{
	*offset += (c == '+') ? move : -move;
}

static int	set_fastmode(int *fast)
{
	*fast *= -1;
	return (1);
}

static int	translation(t_all *param, int key)
{
	t_vector3d	*org;

	org = &param->scene.camera.origin;
	if (key == SDLK_RIGHT)
		move_offset(&org->x, '+', param->move);
	else if (key == SDLK_LEFT)
		move_offset(&org->x, '-', param->move);
	else if (key == SDLK_PAGEUP)
		move_offset(&org->y, '+', param->move);
	else if (key == SDLK_PAGEDOWN)
		move_offset(&org->y, '-', param->move);
	else if (key == SDLK_DOWN)
		move_offset(&org->z, '-', param->move);
	else if (key == SDLK_UP)
		move_offset(&org->z, '+', param->move);
	return (1);
}

void		refresh_surf(void *delay, int type)
{
	t_all	*param;

	param = (t_all*)delay;
	param->data.filter = type;
	clear_render(param->env);
	draw_ui(param);
	put_filter(*param);
	param->env->rend = surface_2_rend(param->env);
}

int			sdl_key(t_all *param, int key)
{
	int			valid_key;

	valid_key = 0;
	if (key == SDLK_ESCAPE)
		quit_exe(*param);
	if (key == SDLK_p)
		screenshot(param, 0);
	if (key == SDLK_RIGHT || key == SDLK_LEFT || key == SDLK_UP
			|| key == SDLK_DOWN || key == SDLK_PAGEUP || key == SDLK_PAGEDOWN)
		valid_key = translation(param, key);
	else if (key == SDLK_q || key == SDLK_w || key == SDLK_e || key == SDLK_a
			|| key == SDLK_s || key == SDLK_d)
		valid_key = rotate_event(param, key);
	else if (key == SDLK_r)
		valid_key = set_fastmode(&param->data.fastmode);
	else if (key == SDLK_c)
		refresh_surf(param, 0);
	else if (key == SDLK_m)
		param->move = (param->move == 0.1f ? 0.8f : 0.1f);
	if (valid_key)
		refresh_img(param);
	return (0);
}
