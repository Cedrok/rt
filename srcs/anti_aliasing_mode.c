/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   anti_aliasing_mode.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cpieri <cpieri@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/24 15:27:36 by bspindle          #+#    #+#             */
/*   Updated: 2018/06/24 17:01:57 by cpieri           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

static t_color	cs(t_color color_1, t_color color_2)
{
	t_color	new;

	new.r = color_1.r + color_2.r;
	new.g = color_1.g + color_2.g;
	new.b = color_1.b + color_2.b;
	return (new);
}

static t_color	unlimited_color_prod(double k, t_color color)
{
	t_color	new;

	new.r = (int)((double)color.r * k);
	new.g = (int)((double)color.g * k);
	new.b = (int)((double)color.b * k);
	return (new);
}

static t_color	color_env(t_env *env, t_color c, t_point p, double coef)
{
	if (p.x > 0)
	{
		c = cs(c, get_color_pixel(env->surf, new_point(p.x - 1, p.y, 0)));
		coef++;
	}
	if (p.x < env->surf->w - 1)
	{
		c = cs(c, get_color_pixel(env->surf, new_point(p.x + 1, p.y, 0)));
		coef++;
	}
	if (p.y > 0)
	{
		c = cs(c, get_color_pixel(env->surf, new_point(p.x, p.y - 1, 0)));
		coef++;
	}
	if (p.y < env->surf->h - 1)
	{
		c = cs(c, get_color_pixel(env->surf, new_point(p.x, p.y + 1, 0)));
		coef++;
	}
	c = unlimited_color_prod(1 / coef, c);
	return (c);
}

static t_color	color_filter(t_env *env, t_color c, t_point p, double coef)
{
	if (p.x > 0)
	{
		c = cs(c, get_color_pixel(env->s_filter, new_point(p.x - 1, p.y, 0)));
		coef++;
	}
	if (p.x < env->surf->w - 1)
	{
		c = cs(c, get_color_pixel(env->s_filter, new_point(p.x + 1, p.y, 0)));
		coef++;
	}
	if (p.y > 0)
	{
		c = cs(c, get_color_pixel(env->s_filter, new_point(p.x, p.y - 1, 0)));
		coef++;
	}
	if (p.y < env->surf->h - 1)
	{
		c = cs(c, get_color_pixel(env->s_filter, new_point(p.x, p.y + 1, 0)));
		coef++;
	}
	c = unlimited_color_prod(1 / coef, c);
	return (c);
}

void	anti_aliasing_mode(t_env *env, t_point p)
{
	double	coef;
	t_color	c;

	coef = 1;
	c = unlimited_color_prod(coef, get_color_pixel(env->surf, p));
	if (!color_to_int(get_color_pixel(env->s_filter, p)) &&
		   	(p.x < env->surf->w - 1 && !color_to_int(get_color_pixel(
			env->s_filter, new_point(p.x + 1, p.y, 0))))
			&& (p.y < env->surf->h - 1 && !color_to_int(get_color_pixel(
						env->s_filter, new_point(p.x, p.y + 1, 0)))))
		c = color_env(env, c, p, coef);
	else
		c = color_filter(env, c, p, coef);
	p.color = color_to_int(c);
    img_put_pixel(env->s_filter, p);
}
