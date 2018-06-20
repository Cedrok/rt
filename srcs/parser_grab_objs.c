/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_grab_objs.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cvautrai <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/06 15:03:41 by cvautrai          #+#    #+#             */
/*   Updated: 2018/06/20 17:18:25 by cvautrai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

static int	shape_type(char *str)
{
	int		res;

	res = -10;
	if (!ft_strcmp(str, "sphere"))
		res = SPHERE;
	else if (!ft_strcmp(str, "plane"))
		res = PLANE;
	else if (!ft_strcmp(str, "cylinder"))
		res = CYLINDER;
	else if (!ft_strcmp(str, "cone"))
		res = CONE;
	else if (!ft_strcmp(str, "torus"))
		res = TORUS;
	ft_strdel(&str);
	return (res);
}

static void	grab_obj_ter(t_shape *obj, char *line)
{
	if (!ft_strncmp(line, "\theight:", 8))
		obj->height = ft_atof(line + 8);
	if (!ft_strncmp(line, "\twidth:", 7))
		obj->width = ft_atof(line + 7);
	if (!ft_strncmp(line, "\topacity:", 9))
		obj->opacity = ft_atof(line + 9);
	if (!ft_strncmp(line, "\tbrillance:", 11))
		obj->brillance = ft_atof(line + 11) * 0.1;
}

static void	grab_obj_bis(t_shape *obj, char *line)
{
	t_vector3d	tmp;
	char		*str_tmp;

	if (!ft_strncmp(line, "\trot:", 5))
	{
		tmp = extract_vd3(line);
		obj->rot = new_matrix(tmp.x, tmp.y, tmp.z);
		obj->inv_rot = matrix_inv(obj->rot);
	}
	if (!ft_strncmp(line, "\tcolor:", 7))
	{
		str_tmp = extract_text(line);
		obj->color = hex2int(str_tmp);
		ft_strdel(&str_tmp);
	}
	if (!ft_strncmp(line, "\tradius:", 8))
	{
		if (obj->type == CONE)
			obj->radius = ft_atof(line + 8) * DEG2RAD;
		else
			obj->radius = ft_atof(line + 8);
	}
}

void		grab_obj(t_scene *scene, int *fd)
{
	char		*line;
	t_shape		obj;

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
		if (!ft_strcmp(line, "\ttexture{"))
			grab_texture(&obj, fd);
		if (!ft_strcmp(line, "\tcut{"))
			grab_cut(&obj, fd);
		grab_obj_bis(&obj, line);
		grab_obj_ter(&obj, line);
	}
	ft_strdel(&line);
	obj = check_obj(&obj);
	if (obj.type != -10)
		ft_lstadd(&scene->shape_lst, ft_lstnew(&obj, sizeof(obj)));
}
