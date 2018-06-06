/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bloc.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cpieri <cpieri@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/04 10:42:20 by cpieri            #+#    #+#             */
/*   Updated: 2018/06/06 10:23:03 by cpieri           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BLOC_H
# define BLOC_H

# include "color.h"
# include "vector.h"
# include "button.h"
# include "label.h"
# include "../../libft/include/libft.h"
# include <string.h>

# define BUTTON		1
# define LABEL		2

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
	t_obj		*lst_obj;
}				t_bloc;

void			lst_add_obj(t_obj **alst, t_obj *new);
t_obj			*new_lst_obj(const void *obj, size_t obj_size, int type);
t_bloc			create_new_bloc(char *s, t_vector4d p, t_color c, int f_size);
t_vector4d		set_child_size(t_bloc *bloc, int pos, int ratio, int margin);

#endif
