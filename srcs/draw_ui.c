/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_ui.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clementpieri <clementpieri@student.42.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/07 10:16:03 by cpieri            #+#    #+#             */
/*   Updated: 2018/06/17 16:03:31 by clementpier      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "SDL_ttf.h"
#include "rt.h"

void     put_string(t_label *str, t_vector4d pos_p, SDL_Renderer *rend)
{
	TTF_Font        *font;
	SDL_Rect		pos;
	SDL_Surface     *text;
	SDL_Texture     *texture;
	SDL_Color		c;

	c.r = str->color.r;
	c.g = str->color.g;
	c.b = str->color.b;
	c.a = 255;
	if ((font = TTF_OpenFont("fonts/neue.ttf", str->font_size)) == NULL)
		ft_putendl("TTF Open Failed");
	if ((text = TTF_RenderText_Blended(font, str->title, c)) == NULL)
		ft_putendl("TTF Render Text Failed");
	if ((texture = SDL_CreateTextureFromSurface(rend, text)) == NULL)
		ft_putendl("SDL Create Texture Failed");
	SDL_QueryTexture(texture, NULL, NULL, &pos.w, &pos.h);
	pos.x = (pos_p.x + (pos_p.z / 2)) - (pos.w / 2);
	pos.y = pos_p.y + ((pos_p.w * str->ratio_marge.w) / 100) + (str->font_size / 2);
	SDL_RenderCopy(rend, texture, NULL, &pos);
	TTF_CloseFont(font);
	SDL_FreeSurface(text);
	SDL_DestroyTexture(texture);
}

void		draw_rect(t_vector4d pos, t_color c, SDL_Renderer *rend)
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

void	draw_bloc(t_bloc *bc, SDL_Renderer *rend)
{
	int			i;
	t_button	*btn;
	t_label		*opt;

	i = 0;
	draw_rect(bc->pos, bc->color, rend);
	if (bc->title.title != NULL)
		put_string(&bc->title, bc->pos, rend);
	if (bc->lst_obj != NULL)
		while (bc->lst_obj[i] != NULL)
		{
			if (bc->lst_obj[i]->type == BUTTON)
			{
				btn = ((t_button*)bc->lst_obj[i]->obj);
				draw_rect(btn->pos, btn->color, rend);
				if (btn->title.title != NULL)
					put_string(&btn->title, btn->pos, rend);
			}
			if (bc->lst_obj[i]->type == LABEL)
			{
				opt = ((t_label*)bc->lst_obj[i]->obj);
				put_string(opt, bc->pos, rend);
			}
			i++;
		}
}

void	draw_ui(t_all *param)
{
	draw_bloc(param->ui.bc_rght, param->env->rend);
	draw_bloc(param->ui.bc_lft, param->env->rend);
	draw_bloc(param->ui.bc_center, param->env->rend);
}