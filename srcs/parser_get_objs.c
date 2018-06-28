/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_get_objs.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cvautrai <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/06 15:03:41 by cvautrai          #+#    #+#             */
/*   Updated: 2018/06/28 08:59:20 by tmilon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

/*
**      Read Objs part and process
*/

static void	default_units(t_shape *obj)
{
	obj->textunit.has_texture = 0;
	obj->textunit.has_rainbow = 0;
	obj->textunit.has_checker = 0;
	obj->textunit.has_waves = 0;
	obj->textunit.x_scale = 1;
	obj->textunit.y_scale = 1;
	obj->textunit.x_offset = 0;
	obj->textunit.y_offset = 0;
	obj->limunit.cut_amount = new_vector_3d_unicoord(1);
	obj->limunit.cut_radius = 0;
}

t_shape		default_shape(int i)
{
	t_shape		obj;
	static int	id = 0;

	obj.id = id;
	id++;
	obj.type = i;
	obj.color = 0xFFFFFF;
	obj.base_color = obj.color;
	obj.origin = new_vector_3d(0, 0, 0);
	obj.height = 0;
	obj.width = 0;
	obj.radius = 1;
	obj.brillance = 0;
	obj.opacity = 1;
	obj.rot = new_matrix(0, 0, 0);
	obj.inv_rot = matrix_inv(obj.rot);
	default_units(&obj);
	return (obj);
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
		if (param->data.nb_shape >= 100)
			return ;
		if (!ft_strcmp(line, "object{"))
		{
			grab_obj(&param->scene, fd);
			param->data.nb_shape += 1;
		}
	}
	ft_strdel(&line);
}
