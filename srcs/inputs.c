/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   inputs.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cpieri <cpieri@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/06 12:36:24 by tmilon            #+#    #+#             */
/*   Updated: 2018/06/14 17:59:15 by cvautrai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"
#include <stdlib.h>
#include <fcntl.h>
#include <sys/stat.h>

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

//	screenshot.c
static char		*super_strjoin(char *str1, char *str2)
{
	char *new;

	new = ft_strjoin(str1, str2);
	ft_strdel(&str1);
	ft_strdel(&str2);
	return (new);
}

static char		*build_name(char *title, int i)
{
	char		*str1;
	char		*str2;
	char		*str3;

	str1 = ft_strdup("screenshots/");
	str2 = ft_strdup(title);
	str3 = super_strjoin(str1, str2);
	str1 = ft_strdup("_");
	str2 = super_strjoin(str3, str1);
	str3 = ft_itoa(i);
	str1 = super_strjoin(str2, str3);
	str2 = ft_strdup(".png");
	str3 = super_strjoin(str1, str2);
	return (str3);
}

static void		screenshot(t_all *param)
{
	static int	i = 1;
	char		*str;
	
	mkdir("screenshots", S_IRWXU | S_IRWXG | S_IRWXO);
	str = build_name(param->env->title, i);
	while (open(str, O_RDONLY) != -1)
	{
		i++;
		ft_strdel(&str);
		str = build_name(param->env->title, i);
	}
	put_filter(*param);
	IMG_SavePNG(param->env->s_filter, str);
	ft_strdel(&str);
	i++;
	ft_putendl("Screenshot saved");
}
//

static void		refresh_surf(t_all *param)
{
	param->data.filter = (param->data.filter < 4) ? param->data.filter + 1 : 0;
	clear_render(param->env);
	draw_ui(param);
	put_filter(*param);
	param->env->rend = surface_2_rend(param->env);
}

int				sdl_key(t_all *param, int key)
{
	int			valid_key;

	valid_key = 0;
	if (key == SDLK_ESCAPE)
		quit_exe(*param);
	if (key == SDLK_p)
		screenshot(param);
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
