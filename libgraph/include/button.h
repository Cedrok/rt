/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   button.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cpieri <cpieri@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/01 11:43:34 by cpieri            #+#    #+#             */
/*   Updated: 2018/06/06 10:23:45 by cpieri           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BUTTON_H
# define BUTTON_H

# include "vector.h"
# include "color.h"

# define VERTICAL_CENTER	1
# define HORIZONTAL_CENTER	2
# define CENTER				3


typedef struct	s_button
{
	int			is_center;
	int			font_size;
	char		*name;
	char		*font_family;
	void		*cllbck_param;
	void		(*callback)(void *);
	t_color		color;
	t_vector4d	pos;
	t_vector2d	ratio;
	int			ratio_2;
	t_vector2d	margin;
}				t_button;

t_button		new_button(char *title, t_color color, int pos, int ratio);
void			set_btn_callback(t_button *btn, void (*clback)(void *),
					void *p);

#endif
