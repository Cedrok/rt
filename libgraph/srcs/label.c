/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   label.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cpieri <cpieri@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/04 15:24:24 by cpieri            #+#    #+#             */
/*   Updated: 2018/06/07 17:02:50 by cpieri           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "label.h"

t_label		new_label(char *s, t_color c, t_vector4d	ratio_marge, int f_size)
{
	t_label		new;

	new.title = s;
	new.color = c;
	new.ratio_marge = ratio_marge;
	new.font_size = f_size;
	return (new);
}