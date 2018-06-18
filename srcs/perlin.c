/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   perlin.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmilon <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/26 15:26:19 by tmilon            #+#    #+#             */
/*   Updated: 2018/06/18 21:27:09 by tmilon           ###   ########.fr       */
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
	n = per->permutation[i + per->permutation[j + 1]] % 8;
	per->grad_b = per->grad_tab[n];
	n = per->permutation[i + 1 + per->permutation[j + 1]] % 8;
	per->grad_c = per->grad_tab[n];
	n = per->permutation[i + 1 + per->permutation[j]] % 8;
	per->grad_d = per->grad_tab[n];
}

/*
	per.a = dotprod_2d(per.grad_a, vector_op_2d(new_vector_2d(x, y),
				new_vector_2d(x0, y0), '-'));
	per.d = dotprod_2d(per.grad_d, vector_op_2d(new_vector_2d(x, y),
				new_vector_2d(x0 + 1, y0), '-'));
	per.b = dotprod_2d(per.grad_b, vector_op_2d(new_vector_2d(x, y),
				new_vector_2d(x0, y0 + 1), '-'));
	per.c = dotprod_2d(per.grad_c, vector_op_2d(new_vector_2d(x, y),
				new_vector_2d(x0 + 1, y0 + 1), '-'));
				*/
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
				new_vector_2d(floor(x), floor(y) + 1), '-'));
	per.c = dotprod_2d(per.grad_c, vector_op_2d(new_vector_2d(x, y),
				new_vector_2d(floor(x) + 1, floor(y) + 1), '-'));
	per.d = dotprod_2d(per.grad_d, vector_op_2d(new_vector_2d(x, y),
				new_vector_2d(floor(x) + 1, floor(y)), '-'));
	coef_inter_x = 3 * (x - floor(x)) * (x - floor(x)) - 2 * (x - floor(x))
		* (x - floor(x)) * (x - floor(x));
	coef_inter_y = 3 * (y - floor(y)) * (y - floor(y)) - 2 * (y - floor(y))
		* (y - floor(y)) * (y - floor(y));
	ab_lisse = per.a + coef_inter_x * (per.d - per.a);
	cd_lisse = per.b + coef_inter_x * (per.c - per.b);
	return (ab_lisse + coef_inter_y * (cd_lisse - ab_lisse));
}

int				*perlin_texture(t_color color, double res_x, double res_y, int limit)
{
	t_perlin_stuff	perlin;
	t_point			p;
	int				*tab;

	perlin_init(&perlin);
	tab = ft_memalloc(sizeof(int) * (limit * limit));
	p = new_point(-1, -1, 0);
	while (++p.y < limit)
	{
		p.x = -1;
		while (++p.x < limit)
		{
			color.r = 0;
			tab[p.y * limit + p.x] = interpolate (0, 0xFFFFFF,
			(noise((double)p.x / res_x , (double)p.y / res_y, perlin) + 1) / 2);
		}
	}
	return (tab);
}
