/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   textures_setup.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmilon <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/12 15:31:26 by tmilon            #+#    #+#             */
/*   Updated: 2018/06/12 15:32:16 by tmilon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"
#include <fcntl.h>
#include <stdlib.h>

static int		*surf_to_int_array(SDL_Surface *surf, t_point p)
{
	t_color	c;
	Uint8	r;
	Uint8	g;
	Uint8	b;
	Uint8	a;
	int		*tab;
	uint32_t	*pixels;
	SDL_Surface	*rgbaImage;

	rgbaImage = SDL_ConvertSurfaceFormat(surf, SDL_PIXELFORMAT_RGBA32, 0);
	tab = ft_memalloc(sizeof(int) * (surf->h * surf->w));
	pixels = (uint32_t *)(rgbaImage->pixels);
	while (++p.y < surf->h)
	{
		p.x = -1;
		while (++p.x < surf->w)
		{
			SDL_GetRGBA(pixels[p.x + p.y * rgbaImage->w], rgbaImage->format,
					&r, &g, &b, &a);
			c = new_color((int)r, (int)g, (int)b);
			tab[p.y * surf->w + p.x] = color_to_int(c);
		}
	}
	SDL_FreeSurface(rgbaImage);
	return (tab);
}

void	setup_textunit(const char *surfpath, t_textunit *textunit)
{
	SDL_Surface	*surf;

	surf = NULL;
	surf = SDL_LoadBMP(surfpath);
	if (!surf)
		return ;
	textunit->has_texture = 1;
	textunit->texture_width = surf->w;
	SDL_LockSurface(surf);
	textunit->texture = surf_to_int_array(surf, new_point(-1, -1, 0));
	SDL_UnlockSurface(surf);
	SDL_FreeSurface(surf);
}
