/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   label.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cpieri <cpieri@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/04 15:24:24 by cpieri            #+#    #+#             */
/*   Updated: 2018/06/04 16:00:12 by cpieri           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "label.h"

t_label		create_new_label(char *s, t_color c, int f_size)
{
	t_label		new;

	new.title = s;
	new.color = c;
	new.font_size = f_size;
	return (new);
}