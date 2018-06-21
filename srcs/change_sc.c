/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   change_sc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cvautrai <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/21 10:06:24 by cvautrai          #+#    #+#             */
/*   Updated: 2018/06/21 10:59:03 by cvautrai         ###   ########.fr       */
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

static void	delshape_func(void *ptr, size_t ok)
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
	param->data.nb_shape = 0;
	param->data.nb_light = 0;
	parse(param, path, &reset);
	SDL_SetWindowTitle(param->env->win, param->env->title);
}

int		change_scene(t_all *param, int key)
{
	if (key == SDLK_0)
		load_scene(param, "scenes/scene0.txt");
	if (key == SDLK_1)
		load_scene(param, "scenes/scene1.txt");
	if (key == SDLK_2)
		load_scene(param, "scenes/scene2.txt");
	return (1);
}
