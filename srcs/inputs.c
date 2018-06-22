/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   inputs.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cpieri <cpieri@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/06 12:36:24 by tmilon            #+#    #+#             */
/*   Updated: 2018/06/22 15:13:55 by cvautrai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"
#include <stdlib.h>

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
		move_rightward(&param->scene.camera, param->move, '+');
	else if (key == SDLK_LEFT)
		move_rightward(&param->scene.camera, param->move, '-');
	else if (key == SDLK_PAGEUP)
		move_upward(&param->scene.camera, param->move, '+');
	else if (key == SDLK_PAGEDOWN)
		move_upward(&param->scene.camera, param->move, '-');
	else if (key == SDLK_DOWN)
		move_forward(&param->scene.camera, param->move, '-');
	else if (key == SDLK_UP)
		move_forward(&param->scene.camera, param->move, '+');
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

static void	reset_cam(t_all *param, t_camera *cam, int key)
{
	if (key == SDLK_BACKSPACE || key == SDLK_DELETE)
	{
		cam->origin = new_vector_3d_unicoord(0);
		cam->rot = new_matrix(0, 0, 0);
		ft_putendl("set camera to {0, 0, 0} with 0 rotation");
		refresh_img(param);
	}
}

int			sdl_key(t_all *param, int key)
{
	int			valid_key;

	reset_cam(param, &param->scene.camera, key);
	valid_key = 0;
	if (key == SDLK_1 || key == SDLK_2 || key == SDLK_3)
		change_scene(param, key);
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
