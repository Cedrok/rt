/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_check_print.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cvautrai <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/06 18:03:42 by cvautrai          #+#    #+#             */
/*   Updated: 2018/06/25 13:13:20 by cvautrai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

static t_vector3d	vd3_norm(t_vector3d n, double min, double max)
{
	t_vector3d	new;

	new.x = ftb_clamp(n.x, min, max);
	new.y = ftb_clamp(n.y, min, max);
	new.z = ftb_clamp(n.z, min, max);
	return (new);
}

t_shape				check_obj(t_shape *obj)
{
	obj->color = ftb_clamp(obj->color, 0, 0xFFFFFF);
	obj->base_color = ftb_clamp(obj->base_color, 0, 0xFFFFFF);
	obj->origin = vd3_norm(obj->origin, -20000, 20000);
	obj->height = ftb_clamp(obj->height, 0, 10000);
	obj->width = ftb_clamp(obj->width, 0, 10000);
	obj->radius = ftb_clamp(obj->radius, 0, 10000);
	obj->brillance = ftb_clamp(obj->brillance, 0, 1);
	obj->opacity = ftb_clamp(obj->opacity, 0, 1);
	obj->textunit.x_scale = ftb_clamp(obj->textunit.x_scale, 0.05, 1000);
	obj->textunit.y_scale = ftb_clamp(obj->textunit.y_scale, 0.05, 1000);
	obj->textunit.x_offset = ftb_clamp(obj->textunit.x_offset, -1000, 1000);
	obj->textunit.y_offset = ftb_clamp(obj->textunit.y_offset, -1000, 1000);
	obj->textunit.has_rainbow = ftb_clamp(obj->textunit.has_rainbow, 0, 1);
	obj->textunit.has_checker = ftb_clamp(obj->textunit.has_checker, 0, 1);
	obj->textunit.has_waves = ftb_clamp(obj->textunit.has_waves, 0, 100);
	obj->limunit.cut_amount = vd3_norm(obj->limunit.cut_amount, -1, 1);
	obj->limunit.cut_radius = ftb_clamp(obj->limunit.cut_radius, 0, 10000);
	obj->limunit.real_position = ftb_clamp(obj->limunit.real_position, 0, 1);
	return (*obj);
}

t_light				check_light(t_light *spot)
{
	spot->origin = vd3_norm(spot->origin, -20000, 20000);
	spot->color = ftb_clamp(spot->color, 0, 0xFFFFFF);
	spot->intensity = ftb_clamp(spot->intensity, 0, 10);
	return (*spot);
}

void				print_infos(int a, int b)
{
	if (a == 0)
		ft_abort("Nothing to see here...");
	if (b == 0)
		ft_abort("I'M BLIND !!!\nOh wait... turn on the light !");
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
