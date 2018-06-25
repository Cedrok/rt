/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   change_sc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cpieri <cpieri@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/21 10:06:24 by cvautrai          #+#    #+#             */
/*   Updated: 2018/06/25 09:25:02 by bspindle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"
#include <stdlib.h>

static void	dellight_func(void *ptr, size_t ok)
{
	t_light *light;

	light = (t_light*)ptr;
	free(light);
	light = NULL;
	(void)ok;
}

void		delshape_func(void *ptr, size_t ok)
{
	t_shape *shape;

	shape = (t_shape*)ptr;
	if (shape->textunit.has_texture == 1)
		free(shape->textunit.texture);
	free(shape);
	shape = NULL;
	(void)ok;
}

static void	load_scene(t_all *param, char *path)
{
	int		reset;

	reset = 1;
	ft_putstr("[] Loading ");
	ft_putendl(path);
	ft_lstdel(&param->scene.shape_lst, &delshape_func);
	ft_lstdel(&param->scene.light_lst, &dellight_func);
	ft_strdel(&param->env->title);
	param->data.fastmode = 1;
	param->data.filter = 4;
	parse(param, path, &reset);
	SDL_SetWindowTitle(param->env->win, param->env->title);
}

void		change_scene(void *p, int key)
{
	t_all	*param;

	param = (t_all*)p;
	if (key == SDLK_1)
		load_scene(param, PATH1);
	if (key == SDLK_2)
		load_scene(param, PATH2);
	if (key == SDLK_3)
		load_scene(param, PATH3);
	refresh_img(param);
}
