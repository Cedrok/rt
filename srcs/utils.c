/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cpieri <cpieri@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/14 11:35:29 by tmilon            #+#    #+#             */
/*   Updated: 2018/06/25 09:11:44 by bspindle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"
#include <math.h>

double		magnitude(t_vector3d v)
{
	return (fabs(v.x) + fabs(v.y) + fabs(v.z));
}

void		ft_abort_free(char *msg, char *line)
{
	free(line);
	ft_abort(msg);
}

int		is_in(t_shape shape, t_light light)
{
	int		(*is_in[10])(t_shape, t_light);

	is_in[SPHERE] = &is_in_sphere;
	is_in[CYLINDER] = &is_in_cylinder;
	is_in[CONE] = &is_in_cone;
	is_in[PLANE] = &is_in_plane;
	return (is_in[shape.type](shape, light));
}

t_vector3d	normals(t_shape shape, t_vector3d point)
{
	t_vector3d	(*normals[10])(t_shape shape, t_vector3d inter);

	normals[SPHERE] = &sphere_normal;
	normals[PLANE] = &plane_normal;
	normals[CYLINDER] = &cylinder_normal;
	normals[CONE] = &cone_normal;
	normals[TORUS] = &torus_normal;
	return (normalize(normals[shape.type](shape, point)));
}

int			collisions(t_shape shape, t_ray ray, double *t)
{
	int	(*collisions[10])(t_shape shape, t_ray ray, double *t);

	collisions[SPHERE] = &intersect_sphere;
	collisions[PLANE] = &intersect_plane;
	collisions[CYLINDER] = &intersect_cylinder;
	collisions[CONE] = &intersect_cone;
	collisions[TORUS] = &intersect_torus;
	return (collisions[shape.type](shape, ray, t));
}

void		int_array_to_surf(SDL_Surface *surf, int *colorarray)
{
	t_point	p;

	p = new_point(-1, -1, 0);
	while (++p.y < surf->h)
	{
		p.x = -1;
		while (++p.x < surf->w)
		{
			p.color = colorarray[p.x + p.y * surf->w];
			img_put_pixel(surf, p);
		}
	}
}
