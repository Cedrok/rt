/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_gets.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cvautrai <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/06 15:03:41 by cvautrai          #+#    #+#             */
/*   Updated: 2018/06/07 13:49:19 by cvautrai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

/*
**      Read Objs part and process
*/

static int	shape_type(char *str)
{
	if (!ft_strcmp(str, "sphere"))
		return (SPHERE);
	else if (!ft_strcmp(str, "plane"))
		return (PLANE);
	else if (!ft_strcmp(str, "cylinder"))
		return (CYLINDER);
	else if (!ft_strcmp(str, "cone"))
		return (CONE);
	else
		ft_abort("incorrect type");
	return (-1);
}

static t_shape	default_shape(int i)
{
	t_shape	obj;

	obj.type = i;
	obj.color = 0xFFFFFF;
	obj.origin = new_vector_3d(0, 0, 0);
	obj.height = 1;
	obj.width = 1;
	obj.radius = 1;
	obj.brillance = 0;
	obj.rot = new_matrix(0, 0, 0);
	obj.inv_rot = matrix_inv(obj.rot);
	obj.textunit.has_texture = 0;
	return (obj);	
}

static void	grab_obj(t_scene *scene, int *fd)
{
	char	*line;
	t_shape	obj;
	t_vector3d	tmp;

	obj = default_shape(-10);
	line = ft_strnew(0);
	while (ft_strcmp(line, "}"))
	{
		ft_strdel(&line);
		if (rt_get_next_line(*fd, &line) <= 0)
			ft_abort_free("grab_obj: rt_gnl <= 0", line);
		if (!ft_strncmp(line, "\ttype:", 6))
			obj.type = shape_type(extract_text(line));
		if (!ft_strncmp(line, "\tpos:", 5))
			obj.origin = extract_vd3(line);
		if (!ft_strncmp(line, "\trot:", 5))
		{
			tmp = extract_vd3(line);
			obj.rot = new_matrix(tmp.x, tmp.y, tmp.z);
			obj.inv_rot = matrix_inv(obj.rot);
		}
		if (!ft_strncmp(line, "\tcolor:", 7))
			obj.color = hex2int(extract_text(line));
		if (!ft_strncmp(line, "\tradius:", 8))
			obj.radius = ft_atof(line + 8);
		if (!ft_strncmp(line, "\theight:", 8))
			obj.height = ft_atof(line + 8);
		if (!ft_strncmp(line, "\twidth:", 7))
			obj.width = ft_atof(line + 7);
		if (!ft_strncmp(line, "\tbrillance:", 11))
			obj.brillance = ft_atof(line + 11);
		if (!ft_strncmp(line, "\ttexture:", 9))
			setup_textunit(extract_text(line), &obj.textunit, 1, 1);
	}
	ft_strdel(&line);
	ft_lstadd(&scene->shape_lst, ft_lstnew(&obj, sizeof(obj)));
}

void		get_objs(t_all *param, int *fd)
{
	char	*line;

	line = ft_strnew(0);
	while (ft_strcmp(line, "#"))
	{
		ft_strdel(&line);
		if (rt_get_next_line(*fd, &line) <= 0)
			ft_abort_free("get_objs: rt_gnl <= 0", line);
		if (!ft_strcmp(line, "object{"))
		{
			grab_obj(&param->scene, fd);
			param->data.nb_shape += 1;
		}
	}
	ft_strdel(&line);
}

/*
**      Read lights part and process
*/

static t_light	default_light()
{
	t_light	light;

	light.origin = new_vector_3d(0, 0, 0);
	light.intensity = 0.5;
	light.color = 0xFFFFFF;
	return (light);
}

static void	grab_spot(t_scene *scene, int *fd)
{
	char	*line;
	t_light	light;

	light = default_light();
	line = ft_strnew(0);
	while (ft_strcmp(line, "}"))
	{
		ft_strdel(&line);
		if (rt_get_next_line(*fd, &line) <= 0)
			ft_abort_free("grab_spot: rt_gnl <= 0", line);
		if (!ft_strncmp(line, "\tpos:", 5))
			light.origin = extract_vd3(line);
		if (!ft_strncmp(line, "\tcolor:", 7))
			light.color = hex2int(extract_text(line));
		if (!ft_strncmp(line, "\tintensity:", 11))
			light.intensity = ft_atof(line + 11);
	}
	ft_strdel(&line);
	ft_lstadd(&scene->light_lst, ft_lstnew(&light, sizeof(light)));
}

void		get_ligths(t_all *param, int *fd)
{
	char	*line;

	line = ft_strnew(0);
	while (ft_strcmp(line, "#"))
	{
		ft_strdel(&line);
		if (rt_get_next_line(*fd, &line) <= 0)
			ft_abort_free("get lights: rt_gnl <= 0", line);
		if (!ft_strcmp(line, "spot{"))
		{
			grab_spot(&param->scene, fd);
			param->data.nb_light += 1;
		}
	}
	ft_strdel(&line);
}
