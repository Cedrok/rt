/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   blur.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cpieri <cpieri@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/26 15:35:16 by cpieri            #+#    #+#             */
/*   Updated: 2018/06/04 17:01:24 by cpieri           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"
#include <math.h>

void	blur_mode(t_env *env, t_point p)
{
	t_point	point;
	double	rs;
	int		iy;
	int		ix;
	double		val = 0;
	double		wsum = 0;

	rs = (10 * 2.57);
	iy = p.y - rs;
	while (iy < (p.y + rs + 1))
	{
		ix = p.x - rs;
		while (ix < (p.x + rs + 1))
		{
			int	max = (0 < ix) ? ix : 0;
			int x = (max < I_WIDTH - 1) ? max : I_WIDTH - 1;
			max = (0 < iy) ? iy : 0;
			int y = (max < I_HEIGHT - 1) ? max : I_HEIGHT - 1;
			int dsq = (ix - p.x) * (ix - p.x) + (iy - p.y) * (iy - p.y);
			int wght = exp(-dsq / (2 * 10 * 10)) / (3.14 * 2 * 10 * 10);
			point = new_point(y, x, 0);
			val += color_to_int(get_color_pixel(env, point)) * wght;
			wsum += wght;
			ix++;
		}
		iy++;
	}
	p.color = (val / wsum);
	img_put_pixel(env, p);
}
