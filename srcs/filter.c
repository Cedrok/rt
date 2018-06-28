/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   filter.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cpieri <cpieri@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/25 10:14:20 by cpieri            #+#    #+#             */
/*   Updated: 2018/06/28 08:46:22 by bspindle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

double			cartoon(double intensity)
{
	if (intensity < 0.3)
		intensity = 0.1;
	else if (intensity < 0.6)
		intensity = 0.4;
	else if (intensity < 1)
		intensity = 0.7;
	return (intensity);
}

static void		sepia_mode(t_env *env, t_point p)
{
	t_color	c;
	t_color	sepia_c;

	c = get_color_pixel(env->surf, p);
	sepia_c.r = (c.r * .393) + (c.g * .769) + (c.b * .189);
	sepia_c.g = (c.r * .349) + (c.g * .686) + (c.b * .168);
	sepia_c.b = (c.r * .272) + (c.g * .534) + (c.b * .131);
	if (sepia_c.r > 255)
		sepia_c.r = 255;
	else if (sepia_c.b > 255)
		sepia_c.b = 255;
	else if (sepia_c.g > 255)
		sepia_c.g = 255;
	p.color = color_to_int(sepia_c);
	img_put_pixel(env->s_filter, p);
}

static void		neg_mode(t_env *env, t_point p)
{
	t_color	c;
	int		neg_c;

	c = get_color_pixel(env->surf, p);
	neg_c = 0xFFFFFF - color_to_int(c);
	p.color = neg_c;
	img_put_pixel(env->s_filter, p);
}

static void		black_mode(t_env *env, t_point p)
{
	t_color		c;
	double		gray_c;

	c = get_color_pixel(env->surf, p);
	gray_c = (0.212 * c.r) + (0.715 * c.g) + (0.072 * c.b) / 3;
	c.r = gray_c;
	c.g = gray_c;
	c.b = gray_c;
	p.color = color_to_int(c);
	img_put_pixel(env->s_filter, p);
}

void			put_filter(t_all param)
{
	t_point		p;
	void		(*f[4])(t_env *, t_point);

	p = new_point(-1, -1, 0);
	f[0] = sepia_mode;
	f[1] = neg_mode;
	f[2] = black_mode;
	f[3] = blur_mode;
	if (param.data.filter != 4)
		while (++p.y < param.env->s_filter->h)
		{
			p.x = -1;
			if ((int)p.y % 5 == 0 || param.data.fastmode == -1)
				while (++p.x < param.env->s_filter->w)
					if ((int)p.x % 5 == 0 || param.data.fastmode == -1)
						if (param.data.filter < 4 && param.data.filter != 4)
							(*f[param.data.filter])(param.env, p);
		}
}
