/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sdl_init.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cpieri <cpieri@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/03 16:26:18 by cpieri            #+#    #+#             */
/*   Updated: 2018/06/04 17:01:10 by cpieri           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

void			create_win_render(t_env *env)
{
	env->win = SDL_CreateWindow("RT", SDL_WINDOWPOS_CENTERED,
		SDL_WINDOWPOS_CENTERED, W_WIDTH, W_HEIGHT, SDL_WINDOW_RESIZABLE);
	SDL_SetWindowMinimumSize(env->win, W_WIDTH, W_HEIGHT);
	env->rend = SDL_CreateRenderer(env->win, -1,
		SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
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
	SDL_SetRenderDrawColor(env->rend, 0x00, 0x2b, 0x36, 1);
	SDL_RenderClear(env->rend);
}

SDL_Renderer	*surface_2_rend(t_env *env)
{
	SDL_Texture	*text;
	SDL_Rect	rectd;

	rectd.x = (W_WIDTH / 2) - (I_WIDTH / 2);
	rectd.y = (W_HEIGHT - I_HEIGHT) - 20;
	rectd.w = I_WIDTH;
	rectd.h = I_HEIGHT;
	text = SDL_CreateTextureFromSurface(env->rend, env->s_filter);
	SDL_BlitSurface(env->surf, NULL, env->s_filter, NULL);
	SDL_RenderCopy(env->rend, text, NULL, &rectd);
	SDL_RenderPresent(env->rend);
	return (env->rend);
}