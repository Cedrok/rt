/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_obj.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cpieri <cpieri@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/19 11:11:20 by cpieri            #+#    #+#             */
/*   Updated: 2018/06/06 10:56:00 by tmilon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <fcntl.h>
#include <stdlib.h>
#include "rt.h"

int		*surf_to_int_array(SDL_Surface *surf, t_point p)
{
	t_color	c;
	Uint8	r;
	Uint8	g;
	Uint8	b;
	Uint8	a;
	int		*tab;
	SDL_Surface *rgbaImage;

	rgbaImage = SDL_ConvertSurfaceFormat(surf, SDL_PIXELFORMAT_RGBA32, 0);
	tab = ft_memalloc(sizeof(int) * (surf->h * surf->w));
	uint32_t* pixels = (uint32_t *)(rgbaImage->pixels);
	while(++p.y < surf->h)
	{
		p.x = -1;
		while (++p.x < surf->w)
		{
			SDL_GetRGBA(pixels[p.x + p.y * rgbaImage->w], rgbaImage->format,
					&r, &g, &b, &a);
			c.r = (int)r;
			c.g = (int)g;
			c.b = (int)b;
			tab[p.y * surf->w + p.x] = color_to_int(c);
		}
	}
	return (tab);
}

void	setup_textunit(const char *surfpath, t_textunit *textunit, double xscale, double yscale)
{
	SDL_Surface	*surf;

	surf = NULL;
	//check if text exists otherwise segfaults
	surf = SDL_LoadBMP(surfpath);
	textunit->has_texture = 1;
	textunit->texture_width = surf->w;
	textunit->xscale = xscale;
	textunit->yscale = yscale;
	SDL_LockSurface(surf);
	textunit->texture = surf_to_int_array(surf, new_point(-1, -1, 0));
	SDL_UnlockSurface(surf);
	SDL_FreeSurface(surf);
}
void	cpy_plane(t_shape *s, char **tab)
{
	//char	*ok = "textures/stones.bmp";
	char	*ok = "textures/lena_gray.bmp";

	if (ft_strcmp(ok, "") != 0)
		setup_textunit(ok, &s->textunit, 1, 1);
	else
		s->textunit.has_texture = 0;
	s->origin = new_vector_3d(ft_atof(tab[1]), ft_atof(tab[2]), ft_atof(tab[3]));
	s->width = ft_atof(tab[9]);
	s->rot = new_matrix(ft_atof(tab[5]), ft_atof(tab[6]), ft_atof(tab[7]));
	s->inv_rot = matrix_inv(s->rot);
	s->type = PLANE;
	s->color = hex2int(tab[4]);
	s->brillance = ft_atof(tab[12]);
	return ;
}


void	cpy_sphere(t_shape *s, char **tab)
{
	//char	*ok = "textures/stones.bmp";
	char	*ok = "textures/lena_gray.bmp";

	if (ft_strcmp(ok, "") != 0)
		setup_textunit(ok, &s->textunit, 0.5, 0.5);
	else
		s->textunit.has_texture = 0;
	s->origin = new_vector_3d(ft_atof(tab[1]), ft_atof(tab[2]), ft_atof(tab[3]));
	s->radius = ft_atof(tab[8]);
	s->rot = new_matrix(ft_atof(tab[5]), ft_atof(tab[6]), ft_atof(tab[7]));
	s->inv_rot = matrix_inv(s->rot);
	s->type = SPHERE;
	s->color = hex2int(tab[4]);
	s->brillance = ft_atof(tab[12]);
	return ;
}

void	cpy_cylinder(t_shape *s, char **tab)
{
	//char	*ok = "textures/stones.bmp";
	char	*ok = "textures/lena_gray.bmp";

	if (ft_strcmp(ok, "") != 0)
		setup_textunit(ok, &s->textunit, 1, 1);
	else
		s->textunit.has_texture = 0;
	s->origin = new_vector_3d(ft_atof(tab[1]), ft_atof(tab[2]), ft_atof(tab[3]));
	s->radius = ft_atof(tab[8]);
	s->height = ft_atof(tab[10]);
	s->rot = new_matrix(ft_atof(tab[5]), ft_atof(tab[6]), ft_atof(tab[7]));
	s->inv_rot = matrix_inv(s->rot);
	s->type = CYLINDER;
	s->color = hex2int(tab[4]);
	s->brillance = ft_atof(tab[12]);
	return ;
}

void	cpy_cone(t_shape *s, char **tab)
{
	//char	*ok = "textures/stones.bmp";
	char	*ok = "textures/lena_gray.bmp";

	if (ft_strcmp(ok, "") != 0)
		setup_textunit(ok, &s->textunit, 1, 1);
	else
		s->textunit.has_texture = 0;
	s->origin = new_vector_3d(ft_atof(tab[1]), ft_atof(tab[2]), ft_atof(tab[3]));
	s->radius = ft_atof(tab[8]) * DEG2RAD;
	s->height = ft_atof(tab[10]);
	s->rot = new_matrix(ft_atof(tab[5]), ft_atof(tab[6]), ft_atof(tab[7]));
	s->inv_rot = matrix_inv(s->rot);
	s->type = CONE;
	s->color = hex2int(tab[4]);
	s->brillance = ft_atof(tab[12]);
	return ;
}
