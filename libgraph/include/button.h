/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   button.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cpieri <cpieri@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/01 11:43:34 by cpieri            #+#    #+#             */
/*   Updated: 2018/06/07 17:03:15 by cpieri           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BUTTON_H
# define BUTTON_H

# include "bloc.h"
# include "label.h"
# include "vector.h"
# include "color.h"

typedef struct	s_button
{
	int			is_center;
	void		*cllbck_param;
	void		(*callback)(void *);
	t_color		color;
	t_vector4d	pos;
	t_vector4d	ratio_marge;
	t_label		title;
}				t_button;

t_button		new_button(t_vector4d parent_pos, t_color c, t_vector4d ratio_marge, int pos);
void			set_title_btn(t_button *btn, char *title, t_vector4d pos, t_color c);
void			set_btn_callback(t_button *btn, void (*clback)(void *),
					void *p);

#endif
