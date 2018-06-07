/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cpieri <cpieri@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/15 11:22:45 by cpieri            #+#    #+#             */
/*   Updated: 2018/06/07 18:54:50 by cvautrai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <fcntl.h>
#include <stdlib.h>
#include "rt.h"

static void		error_msg(int nb_cam, int nb_lght)
{
	ft_putstr("Number of Camera, accepted = 1, value : ");
	ft_putnbr(nb_cam);
	ft_putchar('\n');
	ft_putstr("or Number of Light, accepted >= 1, value : ");
	ft_putnbr(nb_lght);
	ft_putchar('\n');
	ft_abort("or Function GNL Failed");
}

static void		check_line(char *s)
{
	int		i;

	i = 0;
	while (s[i] != '\0')
	{
		if (s[i] != ',' && s[i] != ';')
		{
			while (s[i] != '\0' && s[i] != ';' && s[i] != ',')
			{
				if (!ft_isdigit(s[i]) && s[i] != '.' &&
						(s[i] < 'A' || s[i] > 'Z') && s[i] != '-')
					ft_abort_free("File was wrongly formated !", s);
				i++;
			}
			if (s[i] != '\0' && s[i] != ',' && s[i] != ';')
				ft_abort_free("File was wrongly formated !", s);
		}
		i++;
	}
}

static void		end_lst(t_scene *scene)
{
	t_shape		shape;
	t_light		light;

	shape.type = -1;
	light.color = -1;
	scene->shape_lst = ft_lstnew(&shape, sizeof(shape));
	scene->light_lst = ft_lstnew(&light, sizeof(light));
}

int				parse_old(char *file, t_scene *scene)
{
	char		*line;
	int			fd;
	int			ret;
	int			nb_cam;
	int			nb_lght;

	if ((fd = open(file, O_RDONLY)) <= 0)
		ft_abort("Open failed !");
	end_lst(scene);
	nb_cam = 0;
	nb_lght = 0;
	while ((ret = get_next_line(fd, &line)) > 0)
	{
		if (line != NULL && line[0] != '#')
		{
			check_line(line);
			create_scene(line, scene, &nb_cam, &nb_lght);
		}
		free(line);
	}
	if (ret == -1 || nb_cam != 1 || nb_lght < 1)
		error_msg(nb_cam, nb_lght);
	return (nb_lght);
}
