/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   perlin.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmilon <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/26 15:26:19 by tmilon            #+#    #+#             */
/*   Updated: 2018/06/17 09:33:25 by bspindle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

static void	perlin_permutation(t_perlin_stuff *per)
{
	int	tab[]= {
		131, 13, 201, 95, 96, 53, 194, 233, 7, 225, 140, 36, 103, 30, 69, 142, 8,
		99, 37, 240, 21, 10, 23, 190, 6, 148, 247, 120, 234, 75, 0, 26, 197, 62,
		94, 252, 219, 203, 117, 35, 11, 32, 57, 177, 33, 88, 237, 149, 56, 87, 174,
		20, 125, 136, 171, 168, 68, 175, 74, 165, 71, 134, 139, 48, 27, 166, 77,
		146, 158, 231, 83, 111, 229, 122, 60, 211, 133, 230, 220, 105, 92, 41, 55,
		46, 245, 40, 244, 102, 143, 54, 65, 25, 63, 161, 1, 216, 80, 73, 209, 76,
		132, 187, 208, 89, 18, 169, 200, 196, 135, 130, 116, 188, 159, 86, 164, 100,
		109, 198, 173, 186, 3, 64, 52, 217, 226, 250, 124, 123, 5, 202, 38, 147,
		118, 126, 255, 82, 85, 212, 207, 206, 59, 227, 47, 16, 58, 17, 182, 189, 28,
		42, 223, 183, 170, 213, 119, 248, 152, 2, 44, 154, 163, 70, 221, 153, 101,
		155, 167, 43, 172, 9, 129, 22, 39, 253, 19, 98, 108, 110, 79, 113, 224, 232,
		178, 185, 112, 104, 218, 246, 97, 228, 251, 34, 242, 193, 238, 210, 144, 12,
		191, 179, 162, 241, 81, 51, 145, 235, 249, 14, 239, 107, 49, 192, 214, 31,
		181, 199, 106, 157, 184, 84, 204, 176, 115, 121, 50, 45, 127, 4, 150, 254,
		138, 236, 205, 93, 222, 114, 67, 29, 24, 72, 243, 141, 128, 195, 78, 66,
		215, 61, 156, 180, 151, 160, 137, 91, 90, 15
	};
	per->permutation = tab;
}

static void	perlin_grad_tab(t_perlin_stuff *per)
{
	double	unit;
	t_vector2d	tab[8];

	unit = 0.5 * sqrt(2);
	tab[0] = new_vector_2d(1, 0);
	tab[1] = new_vector_2d(-1, 0);
	tab[2] = new_vector_2d(0, 1);
	tab[3] = new_vector_2d(0, -1);
	tab[4] = new_vector_2d(unit, unit);
	tab[5] = new_vector_2d(-unit, unit);
	tab[6] = new_vector_2d(-unit, -unit);
	tab[7] = new_vector_2d(unit, -unit);
	per->grad_tab = tab;
}

static void	random_tab(t_perlin_stuff *per)
{
	int	ret[512];
	int	i;

	i = 0;
	while (i < 512)
	{
		ret[i] = per->permutation[i % 256];
		i++;
	}
	per->permutation = ret;
}

static void	grad(double x, double y, t_perlin_stuff *per)
{
	int			i;
	int			j;
	int			n;

	i = (int)floor(x) % 256;
	j = (int)floor(y) % 256;
	n = per->permutation[i + per->permutation[j]] % 8;
	per->grad_a = per->grad_tab[n];
	n = per->permutation[i +  1 + per->permutation[j]] % 8;
	per->grad_b = per->grad_tab[n];
	n = per->permutation[i + 1 + per->permutation[j + 1]] % 8;
	per->grad_c = per->grad_tab[n];
	n = per->permutation[i + per->permutation[j + 1]] % 8;
	per->grad_d = per->grad_tab[n];
}

static double	noise(double x, double y, t_perlin_stuff per)
{
	double	a;
	double	b;
	double	c;
	double	d;

	grad(x, y, &per);
	a = dotprod_2d(per.grad_a, vector_op_2d(new_vector_2d(x, y), new_vector_2d(floor(x), floor(y)), '-'));
	b = dotprod_2d(per.grad_b, vector_op_2d(new_vector_2d(x, y), new_vector_2d(floor(x) + 1, floor(y)), '-'));
	c = dotprod_2d(per.grad_c, vector_op_2d(new_vector_2d(x, y), new_vector_2d(floor(x) + 1, floor(y) + 1), '-'));
	d = dotprod_2d(per.grad_d, vector_op_2d(new_vector_2d(x, y), new_vector_2d(floor(x), floor(y) + 1), '-'));
	
	double	coef_inter_x;
	double	coef_inter_y;
	double	ab_lisse;
	double	cd_lisse;

	coef_inter_x = 3 * (x - floor(x)) * (x - floor(x)) - 2 * (x - floor(x)) * (x - floor(x)) * (x - floor(x));
	coef_inter_y = 3 * (y - floor(y)) * (y - floor(y)) - 2 * (y - floor(y)) * (y - floor(y)) * (y - floor(y));
	ab_lisse = a + coef_inter_x * (b - a);
	cd_lisse = c + coef_inter_x * (d - c);
	return (ab_lisse + coef_inter_y * (cd_lisse - ab_lisse));
}

static double	perlin(double x, double y, double res_x, double res_y)
{
	t_perlin_stuff	perlin;

	perlin_permutation(&perlin);
	perlin_grad_tab(&perlin);
	random_tab(&perlin);
	return (noise(x / res_x, y / res_y, perlin));
}

int		**perlin_texture(t_color color, double res_x, double res_y)
{
	int	x;
	int	y;
	int	**tab;
	int	i;

	tab = (int**)malloc(sizeof(int) * 256);
	if (!tab)
		exit (EXIT_FAILURE);
	i = 0;
	while (i < 256)
	{
		tab[i] = (int*)malloc(sizeof(int) * 256);
		if (!tab[i])
			exit (EXIT_FAILURE);
	}
	x = 0;
	while (x < 256)
	{
		y = 0;
		while (y < 256)
		{
			tab[x][y] = color_to_int(color_prod(color, perlin((double)x, (double)y, res_x, res_y)));
			y++;
		}
		x++;
	}
	return (tab);
}
