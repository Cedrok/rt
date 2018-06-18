/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   font.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cpieri <cpieri@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/04 10:10:13 by cpieri            #+#    #+#             */
/*   Updated: 2018/06/18 12:44:08 by cvautrai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

static void	put_string(t_env *env, SDL_Point pt, SDL_Color color, char *str)
{
	TTF_Font		*font;
	SDL_Rect		pos;
	SDL_Surface		*text;
	SDL_Texture		*texture;

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
