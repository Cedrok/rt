/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_get_lights.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cvautrai <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/15 10:33:36 by cvautrai          #+#    #+#             */
/*   Updated: 2018/06/15 10:38:09 by cvautrai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

/*
**      Read lights part and process
*/

static t_light	default_light(void)
{
	t_light	light;

	light.origin = new_vector_3d(0, 0, 0);
	light.intensity = 0.5;
	light.color = 0xFFFFFF;
	return (light);
}

static void		grab_spot(t_scene *scene, int *fd)
{
	char	*line;
	t_light	light;
	char	*str_tmp;

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
		{
			str_tmp = extract_text(line);
			light.color = hex2int(str_tmp);
			ft_strdel(&str_tmp);
		}
		if (!ft_strncmp(line, "\tintensity:", 11))
			light.intensity = ft_atof(line + 11);
	}
	ft_strdel(&line);
	light = check_light(&light);
	ft_lstadd(&scene->light_lst, ft_lstnew(&light, sizeof(light)));
}

void			get_ligths(t_all *param, int *fd)
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
