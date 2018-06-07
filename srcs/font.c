/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   font.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cpieri <cpieri@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/04 10:10:13 by cpieri            #+#    #+#             */
/*   Updated: 2018/06/06 15:03:58 by cpieri           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

static void     put_string(t_env *env, SDL_Point pt, SDL_Color color, char *str)
{
	TTF_Font        *font;
	SDL_Rect		pos;
	SDL_Surface     *text;
	SDL_Texture     *texture;

	if ((font = TTF_OpenFont("fonts/neue.ttf", 16)) == NULL)
		error_exit("OpenFont fail");
	if ((text = TTF_RenderText_Blended(font, str, color)) == NULL)
		error_exit("RenderText_Blended fail");
	if ((texture = SDL_CreateTextureFromSurface(env->ren, text)) == NULL)
		error_exit("CreateTextureFormSurface fail");
	pos.x = pt.x;
	pos.y = pt.y;
	SDL_QueryTexture(texture, NULL, NULL, &pos.w, &pos.h);
	SDL_RenderCopy(env->ren, texture, NULL, &pos);
	TTF_CloseFont(font);
	SDL_FreeSurface(text);
	SDL_DestroyTexture(texture);
}

/*
void            put_string_shadow(t_env *env, int x, int y, char *str)
{
	t_color_4	light;
	t_vector2d	pt;

	light.r = 254;
	light.g = 252;
	light.b = 242;
	light.a = 255;
	pt.x = x;
	pt.y = y;
	put_string(env, pt, light, str);
}
*/