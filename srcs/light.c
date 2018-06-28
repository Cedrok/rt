/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   light.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cpieri <cpieri@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/13 12:33:37 by tmilon            #+#    #+#             */
/*   Updated: 2018/06/28 08:33:31 by tmilon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"
#include <math.h>

static double	get_intensity(t_intersect inter, t_light light, t_data data)
{
	t_vector3d	lightdir;
	double		intensity;

	lightdir = vector_op(light.origin, inter.point, '-');
	intensity = dotprod(normalize(lightdir), inter.normal);
	intensity = intensity <= 0 ? data.ambiantlight * light.intensity :
		intensity * light.intensity + data.ambiantlight * light.intensity;
	intensity = ftb_clamp(intensity, 0, 1);
	return (intensity);
}

static int		fuse(int start, int finish, int tresh)
{
	t_color	a;
	t_color	b;
	t_color	threshold;

	a = int_to_color(start);
	b = int_to_color(finish);
	threshold = int_to_color(tresh);
	a.r = a.r + ftb_clamp(b.r, 0, threshold.r);
	a.g = a.g + ftb_clamp(b.g, 0, threshold.g);
	a.b = a.b + ftb_clamp(b.b, 0, threshold.b);
	return (color_to_int(a));
}

static int		brillance(int start, t_intersect inter, t_light light,
		int filter)
{
	t_vector3d	lightdir;
	double		intensity;
	t_vector3d	reflect;
	double		angle;

	lightdir = normalize(vector_op(light.origin, inter.point, '-'));
	intensity = 2 * dotprod(normalize(inter.normal), lightdir);
	reflect = vector_op(new_vector_3d_unicoord(intensity), inter.normal, '*');
	reflect = vector_op(reflect, lightdir, '-');
	intensity = dotprod(reflect,
			vector_op(inter.dir_to_cam, new_vector_3d_unicoord(-1), '*'));
	intensity = intensity < 0 ? 0 : intensity;
	intensity *= inter.shape_copy.brillance * light.intensity;
	intensity = ftb_clamp(intensity, 0, 1);
	if ((angle = acos(dotprod(normalize(inter.normal), lightdir))) < 0.2)
	{
		intensity *= (0.2 - angle) * 250;
		if (filter == 4)
			intensity = cartoon(intensity);
		return (interpolate(start, light.color, intensity));
	}
	return (start);
}

static int		shadows(t_all *param, t_intersect inter, t_light light,
		int *color)
{
	t_ray		ray;
	t_vector3d	dir;
	t_vector3d	rayorigin;
	t_scene		scene;
	double		shad_color;

	scene = param->scene;
	rayorigin = vector_op(inter.normal, new_vector_3d_unicoord(0.00001), '*');
	rayorigin = vector_op(inter.point, rayorigin, '+');
	dir = vector_op(light.origin, rayorigin, '-');
	ray = new_ray(rayorigin, normalize(dir));
	ray.maxdist = get_length(dir);
	if (inter.shape_copy.opacity != 1.0)
		ray.previous_inter_id = inter.shape_copy.id;
	shad_color = shadow_transp(param, ray, *color);
	if (shad_color != -1)
	{
		shad_color = interpolate(0, shad_color,
				ftb_clamp(light.intensity, 0, 1));
		*color = interpolate(shad_color, *color,
				ftb_clamp(param->data.ambiantlight * light.intensity, 0, 1));
	}
	return (shad_color);
}

int				set_color(t_all *param, t_intersect intersection)
{
	int			ret;
	int			tmp;
	double		intensity;
	t_light		light;
	t_scene		scene;

	ret = 0;
	scene = param->scene;
	while (scene.light_lst != NULL)
	{
		light = *(t_light*)scene.light_lst->content;
		if (light.color == -1)
			break ;
		if (!light.is_hidden)
		{
			intensity = get_intensity(intersection, light, param->data);
			tmp = interpolate(0, intersection.shape_copy.color,
					param->data.filter == 4 ? cartoon(intensity) : intensity);
			if (shadows(param, intersection, light, &tmp) == -1)
				tmp = brillance(tmp, intersection, light, param->data.filter);
			ret = fuse(ret, tmp, light.color);
		}
		scene.light_lst = scene.light_lst->next;
	}
	return (ret);
}
