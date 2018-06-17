/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector_2d_op.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bspindle <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/17 09:34:37 by bspindle          #+#    #+#             */
/*   Updated: 2018/06/17 09:41:37 by bspindle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vector.h"

t_vector2d	vector_op_2d(t_vector2d a, t_vector2d b, char type)
{
	if (type == '-')
		return (new_vector_2d(a.x - b.x, a.y - b.y));
	else if (type == '*')
		return (new_vector_2d(a.x * b.x, a.y * b.y));
	else if (type == '/')
		return (new_vector_2d(a.x / b.x, a.y / b.y));
	return (new_vector_2d(a.x + b.x, a.y + b.y));
}

double		dot_prod_2d(t_vector2d a, t_vector2d b)
{
	return (a.x * b.x + a.y * b.y);
}
