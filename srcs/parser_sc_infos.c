/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_sc_infos.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cvautrai <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/06 14:39:34 by cvautrai          #+#    #+#             */
/*   Updated: 2018/06/06 18:38:10 by cvautrai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

/*
**      Read Scene infos part and process
*/

static void	grab_cam(t_scene *scene, int *fd)
{
	char	*line;
	t_vector3d	origin;
	t_vector3d	tmp;

	line = ft_strnew(0);
	while (ft_strcmp(line, "}"))
	{
		ft_strdel(&line);
		if (rt_get_next_line(*fd, &line) <= 0)
			ft_abort_free("grab_cam: rt_gnl <= 0", line);
		if (!ft_strncmp(line, "\tpos:", 5))
			origin = extract_vd3(line);
		if (!ft_strncmp(line, "\trot:", 5))
			tmp = extract_vd3(line);
	}
	scene->camera = new_cam(origin, tmp.x, tmp.y, tmp.z);
	ft_strdel(&line);
}

void		get_scene_infos(t_all *param, int *fd)
{
	char	*line;
	int		b_cam;
	int		b_title;

	b_cam = 1;
	b_title = 1;
	line = ft_strnew(0);
	while (ft_strcmp(line, "#"))
	{
		ft_strdel(&line);
		if (rt_get_next_line(*fd, &line) <= 0)
			ft_abort_free("get scene infos: rt_gnl <= 0", line);
		if (!ft_strncmp(line, "title:", 6) && b_title)
		{
			param->env->title = extract_text(line);
			b_title = 0;
		}
		if (!ft_strcmp(line, "camera{") && b_cam)
		{
			grab_cam(&param->scene, fd);
			b_cam = 0;
		}
		if (!ft_strncmp(line, "ambiant:", 8))
			param->data.ambiantlight = ft_atof(line + 8);
	}
	ft_strdel(&line);
}
