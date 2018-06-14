/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   img.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cpieri <cpieri@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/12 17:47:21 by cpieri            #+#    #+#             */
/*   Updated: 2018/06/14 14:45:39 by tmilon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

void		create_render(t_all *param)
{
	draw_ui(param);
	setup_multithread(*param);
	if (param->data.filter < 4)
		put_filter(*param);
}

t_color		get_color_pixel(SDL_Surface *surf, t_point p)
{
	t_color	c;
	Uint8	r;
	Uint8	g;
	Uint8	b;
	Uint8	*pixel;

	SDL_LockSurface(surf);
	pixel = (Uint8*)surf->pixels;
	pixel += ((int)p.y * surf->pitch) + ((int)p.x * sizeof(Uint32));
	SDL_GetRGB(*((Uint32*)pixel), surf->format, &r, &g, &b);
	SDL_UnlockSurface(surf);
	c = new_color((int)r, (int)g, (int)b);
	return (c);
}

void	img_put_pixel(SDL_Surface *surf, t_point point)
{
	t_color c;
	Uint32	color;
	Uint8	*pixel;

	c = int_to_color(point.color);
	color = SDL_MapRGB(surf->format, c.r, c.g, c.b);
	SDL_LockSurface(surf);
	pixel = (Uint8*)surf->pixels;
	pixel += ((int)point.y * surf->pitch) + ((int)point.x * sizeof(Uint32));
	*((Uint32*)pixel) = color;
	SDL_UnlockSurface(surf);
}

void	refresh_img(t_all *param)
{
	SDL_FreeSurface(param->env->surf);
	SDL_FreeSurface(param->env->s_filter);
	create_all_surface(param->env);
	clear_render(param->env);
	create_render(param);
	param->env->rend = surface_2_rend(param->env);
}
