/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bloc_2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cpieri <cpieri@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/23 21:35:38 by cpieri            #+#    #+#             */
/*   Updated: 2018/06/23 21:45:40 by cpieri           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "bloc.h"

void		change_bc_fs(t_vector2d win_s, t_bloc *bc, t_vector4d pos)
{
	int		font_size;
	double	format;

	format = win_s.x / win_s.y;
	if (format >= 1.33)
		font_size = (bc->pos.w * pos.y / 100) / 3;
	else
		font_size = ((bc->pos.w * pos.y / 100) / 3) * 0.8;
	bc->title.font_size = font_size;
}

void		change_lb_fs(t_vector2d win_s, t_label *lb, t_bloc *bc)
{
	int		font_size;
	double	format;

	format = win_s.x / win_s.y;
	if (format >= 1.33)
		font_size = (bc->pos.w * lb->ratio_marge.y / 100) / 3;
	else
		font_size = ((bc->pos.w * lb->ratio_marge.y / 100) / 3) * 0.8;
	lb->font_size = font_size;
}
