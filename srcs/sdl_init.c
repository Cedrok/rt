/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sdl_init.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clementpieri <clementpieri@student.42.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/03 16:26:18 by cpieri            #+#    #+#             */
/*   Updated: 2018/06/16 16:13:27 by clementpier      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include "rt.h"

void			create_win_render(t_env *env)
{
	if (!env->title)
		env->title = ft_strdup("RT");
	env->win = SDL_CreateWindow(env->title, SDL_WINDOWPOS_CENTERED,
		SDL_WINDOWPOS_CENTERED, W_WIDTH, W_HEIGHT, SDL_WINDOW_RESIZABLE);
	if (!env->win)
		ft_abort("Error SDL_CreateWindow");
	SDL_SetWindowMinimumSize(env->win, W_WIDTH, W_HEIGHT);
	env->rend = SDL_CreateRenderer(env->win, -1,
		SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
	if (!env->rend)
		ft_abort("Error SDL_CreateRenderer");
}

void			create_all_surface(t_env *env)
{
	env->surf = SDL_CreateRGBSurface(0, I_WIDTH, I_HEIGHT, 32,
			0xff000000, 0x00ff0000, 0x0000ff00, 0x000000ff);
	env->s_filter = SDL_CreateRGBSurface(0, I_WIDTH, I_HEIGHT, 32,
			0xff000000, 0x00ff0000, 0x0000ff00, 0x000000ff);
}

void			clear_render(t_env *env)
{
	if (SDL_SetRenderDrawColor(env->rend, 0x00, 0x2b, 0x36, 1) != 0)
		ft_abort("Error reset RenderDrawColor");
	if (SDL_RenderClear(env->rend) != 0)
		ft_abort("Error SDL_RenderClear");
}

SDL_Renderer	*surface_2_rend(t_env *env)
{
	SDL_Texture	*text;
	t_vector4d	teste;
	SDL_Rect	rectd;

	teste = size_rend(env->w, env->h);
	rectd.x = teste.x;
	rectd.y = teste.y;
	rectd.w = teste.z;
	rectd.h = teste.w;
	text = SDL_CreateTextureFromSurface(env->rend, env->s_filter);
	SDL_BlitSurface(env->surf, NULL, env->s_filter, NULL);
	SDL_RenderCopy(env->rend, text, NULL, &rectd);
	SDL_RenderPresent(env->rend);
	return (env->rend);
}
