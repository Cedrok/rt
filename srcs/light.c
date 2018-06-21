/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   light.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cpieri <cpieri@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/13 12:33:37 by tmilon            #+#    #+#             */
/*   Updated: 2018/06/21 10:32:44 by tmilon           ###   ########.fr       */
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
	intensity = intensity <= 0 ? data.ambiantlight :
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

static int		brillance(int start, t_intersect inter, t_light light, int filter)
{
	t_vector3d	lightdir;
	double		intensity;
	t_vector3d	reflect;

	lightdir = vector_op(light.origin, inter.point, '-');
	intensity = 2 * dotprod(inter.normal, lightdir);
	reflect = vector_op(new_vector_3d_unicoord(intensity), inter.normal, '*');
	reflect = vector_op(reflect, lightdir, '-');
	intensity = dotprod(reflect,
			vector_op(inter.dir_to_cam, new_vector_3d_unicoord(-1), '*')) - 0.5;
	intensity = intensity < 0 ? 0 : intensity;
	intensity = pow(intensity, 14 / (get_length(lightdir) + 0.1));
	intensity *= inter.shape_copy.brillance * light.intensity;
	intensity = ftb_clamp(intensity, 0, 1);
	if (filter == 3)
		intensity = cartoon(intensity);
	return (interpolate(start, light.color, intensity));
}

static int			shadows(t_scene scene, t_intersect inter, t_light light,
		int *color, t_data data)
{
	t_ray		ray;
	t_vector3d	dir;
	t_vector3d	rayorigin;
	double		dist;
	double		tmp;

	rayorigin = vector_op(inter.normal, new_vector_3d_unicoord(0.00001), '*');
	rayorigin = vector_op(inter.point, rayorigin, '+');
	dir = vector_op(light.origin, rayorigin, '-');
	ray = new_ray(rayorigin, normalize(dir));
	dist = get_length(dir);
	tmp = get_nearest_intersection(&ray, scene, &inter, dist);
	while (tmp)
	{
		ray.origin = vector_op(ray.origin, vector_op(ray.direction,
					new_vector_3d_unicoord(tmp), '*'), '+');
		if (inter.shape_copy.opacity != 1.0 && inter.shape_copy.textunit.has_texture)
		{
			inter.shape_copy.color = interpolate(0, inter.shape_copy.color,
	ftb_clamp( 1 - inter.shape_copy.opacity, 0, 1));
			*color = interpolate(inter.shape_copy.color, *color,
	ftb_clamp(1 - inter.shape_copy.opacity, 0, 1));
		}
		*color = interpolate(0, *color, ftb_clamp(data.ambiantlight + 1 - inter.shape_copy.opacity, 0, 1));
		if (inter.shape_copy.opacity != 1.0)
		{
			dist -= tmp;
			ray.previous_inter_id = inter.shape_copy.id;
			tmp = get_nearest_intersection(&ray, scene, &inter, dist);
			if (tmp)
			*color = interpolate(0, *color, ftb_clamp(data.ambiantlight + 1 - inter.shape_copy.opacity, 0, 1));
			else
				return (1);
		}
		else
			return (1);
	}
	return (0);
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
	if (param->data.filter == 3)
		intersection.normal = normalize(intersection.normal);
	while (scene.light_lst != NULL)
	{
		light = *(t_light*)scene.light_lst->content;
		if (light.color == -1)
			break ;
		intensity = get_intensity(intersection, light, param->data);
		if (param->data.filter == 3)
			intensity = cartoon(intensity);
		tmp = interpolate(0, intersection.shape_copy.color, intensity);
		if (!shadows(scene, intersection, light, &tmp, param->data))
			tmp = brillance(tmp, intersection, light, param->data.filter);
		ret = fuse(ret, tmp, light.color);
		scene.light_lst = scene.light_lst->next;
	}
	return (ret);
}
