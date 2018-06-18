/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bloc.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cpieri <cpieri@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/04 10:42:20 by cpieri            #+#    #+#             */
/*   Updated: 2018/06/18 08:50:32 by cpieri           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BLOC_H
# define BLOC_H

# include "color.h"
# include "vector.h"
# include "button.h"
# include "label.h"
# include "../../libft/include/libft.h"
# include <stdlib.h>

# define BUTTON		1
# define LABEL		2

# define LEFT_UP_CONER		0
# define LEFT_DOWN_CONER	1
# define RIGHT_UP_CONER		2
# define RIGHT_DOWN_CONER	3
# define VERTICAL_CENTER	4
# define HORIZONTAL_CENTER	5
# define CENTER				6

typedef	struct		s_obj
{
	void			*obj;
	int				type;
	size_t			obj_size;
	struct s_obj	*next;
}					t_obj;

typedef struct	s_bloc
{
	int			parent;
	t_label		title;
	t_vector4d	pos;
	t_vector2d	margin;
	t_vector2d	ratio;
	t_color		color;
	t_obj		**lst_obj;
}				t_bloc;

t_vector4d		calc_position(t_vector4d parent_size, t_vector4d ratio_marge, int pos);
void			set_title_bloc(t_bloc *bloc, char *title, t_vector4d pos, t_color c);
t_bloc			*new_bloc(t_vector2d w_sz, t_color c, t_vector4d r_m, int pos);
t_obj			*new_obj(void *obj, size_t obj_size, int type);
int				init_lstobj(t_bloc *bloc, int size);

#endif
