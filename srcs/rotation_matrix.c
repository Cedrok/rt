/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rotation_matrix.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cpieri <cpieri@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/13 13:35:35 by tmilon            #+#    #+#             */
/*   Updated: 2018/06/13 15:43:48 by cvautrai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <math.h>
#include "rt.h"

int		rotate_event(t_all *param, int key)
{
	t_camera	*cam;
	t_mat3d		mat;
	double		modif;

	modif = 5;
	cam = &param->scene.camera;
	if (key == SDLK_q)
		rotate_z(&mat, modif);
	if (key == SDLK_e)
		rotate_z(&mat, -modif);
	if (key == SDLK_s)
		rotate_x(&mat, modif);
	if (key == SDLK_w)
		rotate_x(&mat, -modif);
	if (key == SDLK_d)
		rotate_y(&mat, modif);
	if (key == SDLK_a)
		rotate_y(&mat, -modif);
	cam->rot = matrix_mult(cam->rot, mat);
	return (1);
}
