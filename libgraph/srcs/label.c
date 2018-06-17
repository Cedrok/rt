/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   label.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clementpieri <clementpieri@student.42.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/04 15:24:24 by cpieri            #+#    #+#             */
/*   Updated: 2018/06/17 15:56:36 by clementpier      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "label.h"

t_label		new_label(char *s, t_color c, t_vector4d ratio_marge, int f_size)
{
	t_label		new;

	if (s != NULL)
		new.title = ft_strdup(s);
	if (s == NULL)
		new.title = NULL;
	new.color = c;
	new.ratio_marge = ratio_marge;
	new.font_size = f_size;
	return (new);
}

t_label		*new_m_label(char *s, t_color c, t_vector4d ratio_marge, int parent_w)
{
	t_label		*new;

	if (!(new = (t_label*)malloc(sizeof(t_label))))
		return (NULL);
	if (s != NULL)
		new->title = ft_strdup(s);
	if (s == NULL)
		new->title = NULL;
	new->color = c;
	new->ratio_marge = ratio_marge;
	new->font_size = ((parent_w * ratio_marge.y) / 100) / 3;
	return (new);
}