/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cam_move.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Pringles <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/22 12:36:12 by Pringles          #+#    #+#             */
/*   Updated: 2018/06/25 09:34:10 by bspindle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

void	move_forward(t_camera *cam, double move, int sign)
{
	if (sign == '+')
		cam->origin = vector_op(cam->origin, lambda_product_d3(move,
					adjust_direction(new_vector_3d(0, 0, 1), cam->rot)), '+');
	else if (sign == '-')
		cam->origin = vector_op(cam->origin, lambda_product_d3(-move,
					adjust_direction(new_vector_3d(0, 0, 1), cam->rot)), '+');
}

void	move_rightward(t_camera *cam, double move, int sign)
{
	if (sign == '+')
		cam->origin = vector_op(cam->origin, lambda_product_d3(move,
					adjust_direction(new_vector_3d(1, 0, 0), cam->rot)), '+');
	else if (sign == '-')
		cam->origin = vector_op(cam->origin, lambda_product_d3(-move,
					adjust_direction(new_vector_3d(1, 0, 0), cam->rot)), '+');
}

void	move_upward(t_camera *cam, double move, int sign)
{
	if (sign == '+')
		cam->origin = vector_op(cam->origin, lambda_product_d3(move,
					adjust_direction(new_vector_3d(0, 1, 0), cam->rot)), '+');
	else if (sign == '-')
		cam->origin = vector_op(cam->origin, lambda_product_d3(-move,
					adjust_direction(new_vector_3d(0, 1, 0), cam->rot)), '+');
}
