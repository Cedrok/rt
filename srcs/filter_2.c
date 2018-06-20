/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   filter_2.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cpieri <cpieri@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/20 11:35:48 by cpieri            #+#    #+#             */
/*   Updated: 2018/06/20 11:53:42 by cpieri           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

void	cartoon_mode(void *p, int type)
{
	t_all	*param;

	param = (t_all*)p;
	param->data.filter = type;
	clear_render(param->env);
	draw_ui(param);
	create_render(param);
	param->env->rend = surface_2_rend(param->env);
}
