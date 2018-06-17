/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   colors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cpieri <cpieri@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/10 16:53:16 by tmilon            #+#    #+#             */
/*   Updated: 2018/06/17 09:31:21 by bspindle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "color.h"
#include <math.h>

int			color_to_int(t_color c)
{
	return ((((c.r > 0xff) ? 0xff : c.r) << 16) |
			(((c.g > 0xff) ? 0xff : c.g) << 8) |
			((c.b > 0xff) ? 0xff : c.b));
}

t_color		int_to_color(int n)
{
	t_color	a;

	a.r = (n & 0x00FF0000) >> 16;
	a.g = (n & 0x0000FF00) >> 8;
	a.b = (n & 0x000000FF);
	return (a);
}

int			interpolate(int start, int finish, float ratio)
{
	t_color	a;
	t_color	b;

	a = int_to_color(start);
	b = int_to_color(finish);
	a.r = a.r + ((b.r - a.r) * ratio);
	a.g = a.g + ((b.g - a.g) * ratio);
	a.b = a.b + ((b.b - a.b) * ratio);
	return (color_to_int(a));
}

t_color		new_color(int red, int green, int blue)
{
	t_color	ret;

	ret.r = red;
	ret.g = green;
	ret.b = blue;
	return (ret);
}

t_color		color_prod(t_color color, double lambda)
{
	t_color	new;

	new.r = fmax(0, fmin(255, lambda * color.r));
	new.g = fmax(0, fmin(255, lambda * color.g));
	new.b = fmax(0, fmin(255, lambda * color.b));
	return (new);
}
