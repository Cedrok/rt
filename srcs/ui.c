/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ui.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cpieri <cpieri@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/30 11:06:00 by cpieri            #+#    #+#             */
/*   Updated: 2018/06/07 09:37:51 by cpieri           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "SDL_ttf.h"
#include "rt.h"

static void     put_string(t_label str, t_vector4d pos_p, SDL_Renderer *rend)
{
	TTF_Font        *font;
	SDL_Rect		pos;
	SDL_Surface     *text;
	SDL_Texture     *texture;
	SDL_Color		c;

	c.r = str.color.r;
	c.g = str.color.g;
	c.b = str.color.b;
	c.a = 255;
	if ((font = TTF_OpenFont("fonts/neue.ttf", str.font_size)) == NULL)
		ft_putendl("TTF Open Failed");
	if ((text = TTF_RenderText_Blended(font, str.title, c)) == NULL)
		ft_putendl("TTF Render Text Failed");
	if ((texture = SDL_CreateTextureFromSurface(rend, text)) == NULL)
		ft_putendl("SDL Create Texture Failed");
	SDL_QueryTexture(texture, NULL, NULL, &pos.w, &pos.h);
	pos.x = (pos_p.x + (pos_p.z / 2)) - (pos.w / 2);
	pos.y = pos_p.y + str.ratio_marge.w + (str.font_size / 2);
	SDL_RenderCopy(rend, texture, NULL, &pos);
	TTF_CloseFont(font);
	SDL_FreeSurface(text);
	SDL_DestroyTexture(texture);
}

void		draw_fill_render(t_vector4d pos, t_color c, SDL_Renderer *rend)
{
	t_vector2d	point;

	point = new_vector_2d(-1, -1);
	while (++point.y < pos.w)
	{
		point.x = -1;
		while (++point.x < pos.z)
		{
			SDL_SetRenderDrawColor(rend, c.r, c.g, c.b, 255);
			SDL_RenderDrawPoint(rend, pos.x + point.x, pos.y + point.y);
		}
	}
}

t_bloc		create_bloc_filter(t_all *param)
{
	t_bloc		bloc_1;
	t_bloc		bloc_2;
	t_bloc		bloc_3;
	t_button	btn_sepia;
	t_button	btn_gray;
	t_button	btn_neg;
	int 		x, y;

	SDL_GetWindowSize(param->env->win, &x, &y);
	bloc_1 = new_bloc(new_vector_2d(x, y), new_color(0x00, 0x3a, 0x42), new_vector_4d(15, 96, 1.5f, 2), RIGHT_UP_CONER);
	set_title_bloc(&bloc_1, "Les Filtres", new_vector_4d(96, 10, 2, 5), new_color(255, 255, 255));
	btn_sepia = new_button(bloc_1.pos, new_color(102, 59, 42), new_vector_4d(90, 5, 2, 10), HORIZONTAL_CENTER);
	set_title_btn(&btn_sepia, "Sepia", new_vector_4d(101, 55, 0, 0), new_color(255, 255, 255));
	btn_gray = new_button(bloc_1.pos, new_color(101, 101, 101), new_vector_4d(90, 5, 2, 17.5), HORIZONTAL_CENTER);
	set_title_btn(&btn_gray, "Black & White", new_vector_4d(101, 55, 0, 0), new_color(255, 255, 255));
	btn_neg = new_button(bloc_1.pos, new_color(101, 101, 42), new_vector_4d(90, 5, 2, 25), HORIZONTAL_CENTER);
	set_title_btn(&btn_neg, "Negative", new_vector_4d(101, 55, 0, 0), new_color(255, 255, 255));
	bloc_2 = new_bloc(new_vector_2d(x, y), new_color(0x00, 0x3a, 0x42), new_vector_4d(15, 96, 1.5f, 2), LEFT_UP_CONER);
	bloc_3 = new_bloc(new_vector_2d(x, y), new_color(0x00, 0x3a, 0x42), new_vector_4d(63, 10, 1.5f, 2), HORIZONTAL_CENTER);
	draw_fill_render(bloc_1.pos, bloc_1.color, param->env->rend);
	put_string(bloc_1.title, bloc_1.pos, param->env->rend);
	draw_fill_render(btn_sepia.pos, btn_sepia.color, param->env->rend);
	put_string(btn_sepia.title, btn_sepia.pos, param->env->rend);
	draw_fill_render(btn_gray.pos, btn_gray.color, param->env->rend);
	put_string(btn_gray.title, btn_gray.pos, param->env->rend);
	draw_fill_render(btn_neg.pos, btn_neg.color, param->env->rend);
	put_string(btn_neg.title, btn_neg.pos, param->env->rend);
	draw_fill_render(bloc_2.pos, bloc_2.color, param->env->rend);
	draw_fill_render(bloc_3.pos, bloc_3.color, param->env->rend);
	return (bloc_1);
}

int	    	new_ui(t_all *param)
{
	t_bloc		bc_filter;

	bc_filter = create_bloc_filter(param);
	return (0);
}
