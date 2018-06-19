/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_ui.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cpieri <cpieri@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/18 08:57:07 by cpieri            #+#    #+#             */
/*   Updated: 2018/06/19 10:32:43 by cvautrai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

void	free_bloc(t_bloc *bc)
{
	int			i;
	t_button	*btn;
	t_label		*opt;

	i = 0;
	if (bc->lst_obj != NULL)
		while (bc->lst_obj[i] != NULL)
		{
			if (bc->lst_obj[i]->type == BUTTON)
			{
				btn = ((t_button*)bc->lst_obj[i]->obj);
				if (btn->title.title != NULL)
					free(btn->title.title);
				free(btn);
			}
			if (bc->lst_obj[i]->type == LABEL)
			{
				opt = ((t_label*)bc->lst_obj[i]->obj);
				free(opt->title);
				free(opt);
			}
			free(bc->lst_obj[i]);
			i++;
		}
	free(bc->lst_obj);
	if (bc->title.title != NULL)
		free(bc->title.title);
	free(bc);
}

void	free_ui(t_all *param)
{
	free_bloc(param->ui.bc_center);
	free_bloc(param->ui.bc_rght);
	free_bloc(param->ui.bc_lft);
}
