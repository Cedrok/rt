/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cpieri <cpieri@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/14 11:35:29 by tmilon            #+#    #+#             */
/*   Updated: 2018/06/04 17:01:08 by cpieri           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"
#include <math.h>

double	magnitude(t_vector3d v)
{
	return (fabs(v.x) + fabs(v.y) + fabs(v.z));
}

void	ft_abort_free(char *msg, char *line)
{
	free(line);
	ft_abort(msg);
}
