/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   label.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cpieri <cpieri@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/04 15:26:55 by cpieri            #+#    #+#             */
/*   Updated: 2018/06/23 21:36:09 by cpieri           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LABEL_H
# define LABEL_H

# include "../../libft/include/libft.h"
# include "vector.h"
# include "color.h"

typedef struct	s_label
{
	char		*title;
	int			font_size;
	t_vector4d	ratio_marge;
	t_color		color;
}				t_label;

t_label			new_label(char *s, t_color c,
		t_vector4d ratio_marge, int f_size);
t_label			*new_m_label(char *s, t_color c,
		t_vector4d ratio_marge, int parent_w);

#endif
