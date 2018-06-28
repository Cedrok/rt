/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   textures_setup.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmilon <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/12 15:31:26 by tmilon            #+#    #+#             */
/*   Updated: 2018/06/28 09:12:12 by bspindle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"
#include <fcntl.h>
#include <stdlib.h>

static int	*surf_to_int_array(SDL_Surface *surf, t_point p)
{
	t_color		c;
	Uint8		a;
	int			*tab;
	uint32_t	*pixels;
	SDL_Surface	*rgbaimage;

	rgbaimage = SDL_ConvertSurfaceFormat(surf, SDL_PIXELFORMAT_RGBA32, 0);
	if (!(tab = ft_memalloc(sizeof(int) * (surf->h * surf->w))))
		ft_abort("Malloc failed in texture init.\n");
	pixels = (uint32_t *)(rgbaimage->pixels);
	c = new_color(0, 0, 0);
	while (++p.y < surf->h)
	{
		p.x = -1;
		while (++p.x < surf->w)
		{
			SDL_GetRGBA(pixels[p.x + p.y * rgbaimage->w], rgbaimage->format,
					(Uint8*)&c.r, (Uint8*)&c.g, (Uint8*)&c.b, &a);
			tab[p.y * surf->w + p.x] = color_to_int(c);
		}
	}
	SDL_FreeSurface(rgbaimage);
	return (tab);
}

t_vector3d	bump_mapping(t_vector3d normal, int colorint)
{
	double	mult;
	t_color	color;

	color = int_to_color(colorint);
	mult = color.b / 255.0
		+ color.r / 255.0
		+ color.g / 255.0;
	mult /= 3.0;
	return (vector_op(normal, new_vector_3d_unicoord(mult), '*'));
}

void		setup_textunit(const char *surfpath, t_textunit *textunit)
{
	SDL_Surface	*surf;

	surf = NULL;
	if (ft_strcmp(surfpath, "perlin") == 0)
	{
		textunit->texture_width = 800;
		textunit->texture = perlin_texture(
				50, 50, textunit->texture_width);
	}
	else
	{
		surf = IMG_Load(surfpath);
		if (!surf)
			return ;
		textunit->texture_width = surf->w;
		textunit->texture = surf_to_int_array(surf, new_point(-1, -1, 0));
		SDL_FreeSurface(surf);
	}
	textunit->has_texture = 1;
}

void		get_uv_mapping_coord(double *u, double *v, t_intersect i, t_shape s)
{
	if (s.type == PLANE)
	{
		*u = (i.point.x + s.width) / (2 *
				(s.width == 0 ? s.textunit.x_scale : s.width));
		*v = (-i.point.z + s.width) / (2 *
				(s.width == 0 ? s.textunit.y_scale : s.width));
	}
	if (s.type == SPHERE)
	{
		*u = 0.5 + (atan2(i.normal.z, i.normal.x) / (2 * PI));
		*v = 0.5 - (asin(i.normal.y) / PI);
	}
	else if (s.type == CYLINDER)
	{
		*u = 0.5 + atan2(i.normal.z, i.normal.x) / (2 * PI);
		*v = i.point.y / (s.height == 0 ? s.textunit.y_scale : s.height);
	}
	else if (s.type == CONE)
	{
		*u = 0.5 + atan2(i.normal.z, i.normal.x) / (2 * PI);
		*v = i.point.y / (s.height == 0 ? s.textunit.y_scale : s.height);
	}
}
