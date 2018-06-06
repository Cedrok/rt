/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_check_print.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cvautrai <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/06 18:03:42 by cvautrai          #+#    #+#             */
/*   Updated: 2018/06/06 18:07:23 by cvautrai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

/*
static double		double_norm(double n, int min, int max)
{
	if (n < min)
		return (min);
	else if (n > max)
		return (max);
	else
		return (n);
}

static t_vect_d3	vd3_norm(t_vect_d3 n, int min, int max)
{
	t_vect_d3	new;

	new.x = double_norm(n.x, min, max);
	new.y = double_norm(n.y, min, max);
	new.z = double_norm(n.z, min, max);
	return (new);
}

static void			check_obj(t_object *obj)
{
	if (!obj->name)
		obj->name = ft_strdup("empty");
	obj->center = vd3_norm(obj->center, -20000, 20000);
	if (!ft_strcmp("sphere", obj->name))
		obj->axis = vd3_norm(obj->axis, -20000, 20000);
	else
		obj->axis = lambda_product_d3(CONV,
				vd3_norm(obj->axis, -20000, 20000));
	obj->color = vd3_norm(obj->color, 0, 255);
	if (ft_strcmp("cone", obj->name))
		obj->radius = double_norm(obj->radius, 0, 10000);
	else
		obj->radius = tan(double_norm(obj->radius, 0, 10000) * CONV);
}

void				check_items(t_scene *scene)
{
	int			i;

	scene->cam.pos = vd3_norm(scene->cam.pos, -20000, 20000);
	scene->cam.dir = vd3_norm(scene->cam.dir, -20000, 20000);
	i = 0;
	while (i < scene->obj_nbr)
	{
		check_obj(&scene->obj[i]);
		i++;
	}
	i = 0;
	while (i < scene->spot_nbr)
	{
		scene->spot[i].pos = vd3_norm(scene->spot[i].pos, -20000, 20000);
		scene->spot[i].color = vd3_norm(scene->spot[i].color, 0, 255);
		i++;
	}
}
*/
void				print_infos(int a, int b)
{
	if (a == 0)
	{
		ft_putendl("Nothing to see here...");
		return ;
	}
	if (b == 0)
	{
		ft_putendl("I'M BLIND !!!\nOh wait... turn on the light !");
		return ;
	}
	ft_putstr("[] ");
	ft_putnbr(a);
	if (a <= 1)
		ft_putstr(" object, ");
	else
		ft_putstr(" objects, ");
	ft_putnbr(b);
	if (b <= 1)
		ft_putendl(" light");
	else
		ft_putendl(" lights");
}
