/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cpieri <cpieri@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/01 16:10:40 by cpieri            #+#    #+#             */
/*   Updated: 2018/06/06 10:13:39 by cpieri           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef COLOR_H
# define COLOR_H

typedef struct	s_color
{
	int			r;
	int			g;
	int			b;
}				t_color;

typedef struct	s_color_4
{
	int			r;
	int			g;
	int			b;
	int			a;
}				t_color_4;

int				interpolate(int start, int finish, float ratio);
int				color_to_int(t_color c);
t_color			int_to_color(int n);
t_color			new_color(int red, int green, int blue);

#endif
