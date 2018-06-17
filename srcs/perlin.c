/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   perlin.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmilon <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/26 15:26:19 by tmilon            #+#    #+#             */
/*   Updated: 2018/06/17 10:55:14 by bspindle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

static void		grad(double x, double y, t_perlin_stuff *per)
{
	int			i;
	int			j;
	int			n;

	i = (int)floor(x) % 256;
	j = (int)floor(y) % 256;
	n = per->permutation[i + per->permutation[j]] % 8;
	per->grad_a = per->grad_tab[n];
	n = per->permutation[i + 1 + per->permutation[j]] % 8;
	per->grad_b = per->grad_tab[n];
	n = per->permutation[i + 1 + per->permutation[j + 1]] % 8;
	per->grad_c = per->grad_tab[n];
	n = per->permutation[i + per->permutation[j + 1]] % 8;
	per->grad_d = per->grad_tab[n];
}

static double	noise(double x, double y, t_perlin_stuff per)
{
	double	coef_inter_x;
	double	coef_inter_y;
	double	ab_lisse;
	double	cd_lisse;

	grad(x, y, &per);
	per.a = dotprod_2d(per.grad_a, vector_op_2d(new_vector_2d(x, y),
				new_vector_2d(floor(x), floor(y)), '-'));
	per.b = dotprod_2d(per.grad_b, vector_op_2d(new_vector_2d(x, y),
				new_vector_2d(floor(x) + 1, floor(y)), '-'));
	per.c = dotprod_2d(per.grad_c, vector_op_2d(new_vector_2d(x, y),
				new_vector_2d(floor(x) + 1, floor(y) + 1), '-'));
	per.d = dotprod_2d(per.grad_d, vector_op_2d(new_vector_2d(x, y),
				new_vector_2d(floor(x), floor(y) + 1), '-'));
	coef_inter_x = 3 * (x - floor(x)) * (x - floor(x)) - 2 * (x - floor(x))
		* (x - floor(x)) * (x - floor(x));
	coef_inter_y = 3 * (y - floor(y)) * (y - floor(y)) - 2 * (y - floor(y))
		* (y - floor(y)) * (y - floor(y));
	ab_lisse = per.a + coef_inter_x * (per.b - per.a);
	cd_lisse = per.c + coef_inter_x * (per.d - per.c);
	return (ab_lisse + coef_inter_y * (cd_lisse - ab_lisse));
}

int				**perlin_texture(t_color color, double res_x, double res_y)
{
	t_perlin_stuff	perlin;
	int				x;
	int				y;
	int				**tab;

	perlin_init(&perlin);
	tab = perlin_tab_init();
	x = 0;
	while (x < 256)
	{
		y = 0;
		while (y < 256)
		{
			tab[x][y] = color_to_int(color_prod(color,
						noise((double)x / res_x, (double)y / res_y, perlin)));
			y++;
		}
		x++;
	}
	return (tab);
}
