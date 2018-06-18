/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   textures_setup.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmilon <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/12 15:31:26 by tmilon            #+#    #+#             */
/*   Updated: 2018/06/18 16:27:18 by tmilon           ###   ########.fr       */
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
	tab = ft_memalloc(sizeof(int) * (surf->h * surf->w));
	pixels = (uint32_t *)(rgbaimage->pixels);
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

void		setup_textunit(const char *surfpath, t_textunit *textunit)
{
	SDL_Surface	*surf;

	surf = NULL;
	surf = IMG_Load(surfpath);
	if (!surf)
		return ;
	textunit->has_texture = 1;
	textunit->texture_width = surf->w;
	SDL_LockSurface(surf);
	textunit->texture = surf_to_int_array(surf, new_point(-1, -1, 0));
	//surf_to_int_array(surf, new_point(-1, -1, 0));
	//textunit->texture_width = 2048;
	//textunit->texture = perlin_texture(new_color(255, 0, 0), 1024, 1024, textunit->texture_width);
	SDL_UnlockSurface(surf);
	SDL_FreeSurface(surf);
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
