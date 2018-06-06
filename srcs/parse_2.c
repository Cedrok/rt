/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cpieri <cpieri@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/17 11:46:13 by cpieri            #+#    #+#             */
/*   Updated: 2018/06/04 17:01:14 by cpieri           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"
#include <stdlib.h>
#include <fcntl.h>

static void	init_tabof_f(int av, void (*cpy_func[4][2])(t_shape *, char **))
{
	int		i;
	int		y;

	if (av == 0)
	{
		cpy_func[0][0] = (void*)ft_strdup("SPHERE");
		cpy_func[0][1] = cpy_sphere;
		cpy_func[1][0] = (void*)ft_strdup("CYLINDER");
		cpy_func[1][1] = cpy_cylinder;
		cpy_func[2][0] = (void*)ft_strdup("PLANE");
		cpy_func[2][1] = cpy_plane;
		cpy_func[3][0] = (void*)ft_strdup("CONE");
		cpy_func[3][1] = cpy_cone;
	}
	else if (av == 1)
	{
		i = 0;
		while (i <= 3)
		{
			y = 0;
			while (y <= 0)
				free(cpy_func[i][y++]);
			i++;
		}
	}
}

static void	create_obj(char **tab, t_scene *scene, int len_color, char *s)
{
	void		(*cpy_func[4][2])(t_shape *, char **);
	t_shape		ret;
	int			i;

	if (len_color != 6)
		parsing_quit("Line was wrongly formated !", tab, s);
	init_tabof_f(0, cpy_func);
	i = 0;
	while (i < 4 && ft_strcmp(tab[0], (char*)cpy_func[i][0]) != 0)
		i++;
	if (i == 4)
	{
		init_tabof_f(1, cpy_func);
		parsing_quit("Line was wrongly formated !", tab, s);
	}
	(*cpy_func[i][1])(&ret, tab);
	ft_lstadd(&scene->shape_lst, ft_lstnew(&ret, sizeof(ret)));
	init_tabof_f(1, cpy_func);
}

static void	cpy_cam(char **tab, t_scene *scene)
{
	t_vector3d	org;
	double		x;
	double		y;
	double		z;

	org = new_vector_3d(ft_atof(tab[1]), ft_atof(tab[2]), ft_atof(tab[3]));
	x = ft_atof(tab[5]);
	y = ft_atof(tab[6]);
	z = ft_atof(tab[7]);
	scene->camera = new_cam(org, x, y, z);
}

static void	scene_light(char **tab, t_scene *scene, int len_color, char *s)
{
	t_light		lght;
	t_vector3d	org;

	if (len_color != 6)
		parsing_quit("Line was wrongly formated !", tab, s);
	org = new_vector_3d(ft_atof(tab[1]), ft_atof(tab[2]), ft_atof(tab[3]));
	lght = new_light(org, ft_atof(tab[11]), hex2int(tab[4]));
	ft_lstadd(&scene->light_lst, ft_lstnew(&lght, sizeof(lght)));
}

void		create_scene(char *s, t_scene *scene, int *nb_cam, int *nb_lght)
{
	char	**tab;
	int		i;

	i = 0;
	tab = ft_strsplit(s, ',');
	while (tab[i] != NULL)
		i++;
	if (i != 13)
		parsing_quit("Line was wrongly formated !", tab, s);
	i = ft_strlen(tab[4]);
	if (ft_strcmp(tab[0], "CAMERA") == 0)
	{
		*nb_cam = *nb_cam + 1;
		cpy_cam(tab, scene);
	}
	else if (ft_strcmp(tab[0], "LIGHT") == 0)
	{
		*nb_lght = *nb_lght + 1;
		scene_light(tab, scene, i, s);
	}
	else
		create_obj(tab, scene, i, s);
	free_multiarray(tab);
}
