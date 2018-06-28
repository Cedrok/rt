/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_grab_extras.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cvautrai <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/06 15:03:41 by cvautrai          #+#    #+#             */
/*   Updated: 2018/06/28 09:00:24 by tmilon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

void		grab_cut(t_shape *obj, int *fd)
{
	char	*line;

	line = ft_strnew(0);
	while (ft_strcmp(line, "\t}"))
	{
		ft_strdel(&line);
		if (rt_get_next_line(*fd, &line) <= 0)
			ft_abort_free("grab_cut: rt_gnl <= 0", line);
		if (!ft_strncmp(line, "\t\tamount:", 9))
			obj->limunit.cut_amount = extract_vd3(line);
		if (!ft_strncmp(line, "\t\tradius:", 9))
			obj->limunit.cut_radius = ft_atof(line + 9);
	}
	ft_strdel(&line);
}

static void	grab_texture_bis(t_shape *obj, char *line)
{
	if (!ft_strncmp(line, "\t\tx_offset:", 11))
		obj->textunit.x_offset = ft_atof(line + 11);
	if (!ft_strncmp(line, "\t\ty_offset:", 11))
		obj->textunit.y_offset = ft_atof(line + 11);
	if (!ft_strncmp(line, "\t\trainbow:", 10))
		obj->textunit.has_rainbow = ft_atof(line + 10);
	if (!ft_strncmp(line, "\t\tchecker:", 10))
		obj->textunit.has_checker = ft_atof(line + 10);
	if (!ft_strncmp(line, "\t\twaves:", 8))
		obj->textunit.has_waves = ft_atof(line + 8);
}

void		grab_texture(t_shape *obj, int *fd)
{
	char	*line;
	char	*path;

	line = ft_strnew(0);
	path = NULL;
	while (ft_strcmp(line, "\t}"))
	{
		ft_strdel(&line);
		if (rt_get_next_line(*fd, &line) <= 0)
			ft_abort_free("grab_texture: rt_gnl <= 0", line);
		if (!ft_strncmp(line, "\t\tpath:", 7))
			path = extract_text(line);
		if (!ft_strncmp(line, "\t\tx_scale:", 10))
			obj->textunit.x_scale = ft_atof(line + 10);
		if (!ft_strncmp(line, "\t\ty_scale:", 10))
			obj->textunit.y_scale = ft_atof(line + 10);
		grab_texture_bis(obj, line);
		if (!ft_strcmp(line, "}"))
			ft_abort_free("no end to texture definition", line);
	}
	if (path)
		setup_textunit(path, &obj->textunit);
	ft_strdel(&path);
	ft_strdel(&line);
}
