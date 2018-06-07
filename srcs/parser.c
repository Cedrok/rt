/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cvautrai <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/06 13:39:25 by cvautrai          #+#    #+#             */
/*   Updated: 2018/06/07 10:25:47 by cvautrai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"
#include <fcntl.h>

/*
**	Main parsing function
*/

static void	check_booleans(t_all *param, int b_objs, int b_lights)
{
	if (b_objs)
		param->data.nb_shape = 0;
	if (b_lights)
		param->data.nb_light = 0;
}

static void	which_section(t_all *param, int *fd, char *line)
{
	static int		b_infos = 1;
	static int		b_objs = 1;
	static int		b_lights = 1;

	if (!ft_strcmp(line, "# Scene informations") && b_infos)
	{
		get_scene_infos(param, fd);
		b_infos = 0;
	}
	if (!ft_strcmp(line, "# Objects") && b_objs)
	{
		get_objs(param, fd);
		b_objs = 0;
	}
	if (!ft_strcmp(line, "# Lights") && b_lights)
	{
		get_ligths(param, fd);
		b_lights = 0;
	}
	if (!ft_strcmp(line, "##END##"))
		check_booleans(param, b_objs, b_lights);
}

static void	end_lst(t_scene *scene)
{
	t_shape	shape;
	t_light	light;

	shape.type = -1;
	light.color = -1;
	scene->shape_lst = ft_lstnew(&shape, sizeof(shape));
	scene->light_lst = ft_lstnew(&light, sizeof(light));
}

void		parse(t_all *param, char *arg)
{
	int		fd;
	int		gnl;
	char	*line;
	int		do_it;

	if ((fd = open(arg, O_RDONLY)) <= 0)
		ft_abort("open fail");
	end_lst(&param->scene);
	gnl = 1;
	line = NULL;
	do_it = 1;
	while (gnl)
	{
		if ((gnl = get_next_line(fd, &line)) == -1)
			ft_abort("gnl fail");
		if (do_it)
			which_section(param, &fd, line);
		if (!ft_strcmp(line, "##END##"))
		{
			do_it = 0;//break ; ?
		}
		ft_strdel(&line);
	}
	close(fd);
//	check_items(scene);
	print_infos(param->data.nb_shape, param->data.nb_light);
}
