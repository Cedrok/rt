/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rt.h                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cpieri <cpieri@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/18 17:15:16 by tmilon            #+#    #+#             */
/*   Updated: 2018/06/14 09:58:13 by cvautrai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RT_H
# define RT_H

# include <SDL.h>
# include <SDL_ttf.h>
# include <SDL_image.h>
# include "../libgraph/include/libgraph.h"
# include "../libft/include/libft.h"

#include <stdio.h>

/*
 ******************************* Disp defines *********************************
 */

# define I_WIDTH			1280
# define I_HEIGHT			720
# define W_WIDTH			1920
# define W_HEIGHT			1080
# define PIC_LIMIT			I_WIDTH * I_HEIGHT
# define DIST_MAX			2000000
# define DIST_MIN			0.00000001
# define THREAD_LIMIT		4
# define PI					3.141592653

/*
 ******************************* Item defines *********************************
 */

# define SPHERE				0
# define CAMERA				1
# define LIGHT				2
# define PLANE				3
# define CONE				4
# define CYLINDER			5
# define TORUS				6

/*
 ** Basic structs
 */

typedef struct		s_point
{
	int			x;
	int			y;
	int			color;
}					t_point;

typedef struct		s_calcunit
{
	double			a;
	double			b;
	double			c;
	double			delta;
	double			t0;
	double			t1;
	t_vector3d		get_in;
	t_vector3d		get_out;
}					t_calcunit;

/*
 ** Objects struct
 */

typedef struct		s_camera
{
	t_vector3d		origin;
	t_mat3d			rot;
	double			w;
	double			h;
	double			fov;
	double			aspect_ratio;
}					t_camera;

typedef struct		s_light
{
	t_vector3d		origin;
	double			intensity;
	int				color;
}					t_light;

typedef struct		s_textunit
{
	int				has_texture;
	int				has_rainbow;
	int				has_checker;
	int				*texture;
	int				texture_width;
	double			x_scale;
	double			y_scale;
	double			x_offset;
	double			y_offset;
}					t_textunit;

typedef struct		s_limunit
{
	t_vector3d	cut_amount;
	double		cut_radius;
	int			real_position;
}					t_limunit;

typedef struct		s_shape
{
	int				id;
	int				type;
	int				color;
	t_vector3d		origin;
	double			height;
	double			width;
	double			radius;
	double			brillance;
	double			opacity;
	t_mat3d			rot;
	t_mat3d			inv_rot;
	t_textunit		textunit;
	t_limunit		limunit;
}					t_shape;

/*
 ** Structs for raytracing
 */

typedef struct		s_ray
{
	t_vector3d		origin;
	t_vector3d		direction;
	int				previous_inter_id;
}					t_ray;

typedef struct		s_intersect
{
	int				color;
	t_vector3d		point;
	t_vector3d		normal;
	t_vector3d		dir_to_cam;
	t_shape			shape_copy;
}					t_intersect;

/*
 ** SDL handling structs
 */

typedef struct		s_env
{
	SDL_Window		*win;
	SDL_Renderer	*rend;
	SDL_Surface		*surf;
	SDL_Surface		*s_filter;
	int				loop;
	char			*title;
	int				w;
	int				h;
}					t_env;

/*
 ** Environement Struct
 */

typedef struct		s_data
{
	double			ambiantlight;
	int				fastmode;
	int				filter;
	int				nb_light;
	int				nb_shape;
}					t_data;

typedef struct		s_scene
{
	t_list			*shape_lst;
	t_list			*light_lst;
	t_camera		camera;
}					t_scene;

typedef struct		s_ui
{
	t_bloc			*bc_rght;
	t_bloc			*bc_center;
	t_bloc			*bc_lft;
}					t_ui;

typedef struct		s_all
{
	t_scene			scene;
	t_env			*env;
	t_data			data;
	t_ui			ui;
	t_point			point;
	int				maxy;
	int				*colorarray;
}					t_all;

/*
 **	Calc_struct
 */

typedef struct		s_thread_param
{
	t_env			*unit;
	t_data			data;
	int				maxy;
}					t_thread_param;

/*
 ** Initstruct
 */

t_light				new_light(t_vector3d origin, double intensity, int color);//?
t_ray				new_ray(t_vector3d o, t_vector3d d);
t_point				new_point(int x, int y, int color);
t_shape				new_shape(int type, void *shape, int color);
t_scene				new_env(t_list *shape_lst, t_list *lightlist);
t_camera			new_cam(t_vector3d orig, double x, double y, double z);

/*
 ** Intersection checking
 */

int					intersect_sphere(t_shape shape, t_ray ray, double *t);
int					intersect_plane(t_shape shape, t_ray ray, double *t);
int					intersect_cylinder(t_shape shape, t_ray ray, double *t);
int					intersect_cone(t_shape shape, t_ray ray, double *t);

/*
 ** Normal fetchers
 */

t_vector3d			sphere_normal(t_shape shape, t_vector3d intersection_point);
t_vector3d			plane_normal(t_shape shape, t_vector3d intersection_point);
t_vector3d			cylinder_normal(t_shape shape, t_vector3d intersection_point);
t_vector3d			cone_normal(t_shape shape, t_vector3d intersection_point);

/*
 ** Display functs
 */

int					no_collisions(t_list *shape_lst,
		t_intersect inter, t_light light);
int					set_color(t_scene scene, t_intersect intersection, t_data data);
int					interpolate(int start, int finish, float ratio);
//void				raytrace(t_scene scene, t_env *unit, t_point p, t_data data);
double			get_nearest_intersection(t_ray *ray, t_scene scene,
		t_intersect *nearest_intersect, double maxdist);
void				setup_multithread(t_all param);
//void				setup_multithread(t_scene scene, t_env *unit, t_data data);

/*
 ** Texture
 */

int			texture(int color, t_intersect i, t_shape s);
void		setup_textunit(const char *surfpath, t_textunit *textunit);
void	get_uv_mapping_coord(double *u, double *v, t_intersect i, t_shape s);

/*
 ** Limiters
 */

void				limit_sphere(t_shape shape, t_ray ray,
		double *t,t_calcunit calc);
void				limit_cylinder(t_shape shape, t_ray ray,
		double *t, t_calcunit calc);
void				limit_cone(t_shape shape, t_ray ray,
		double *t, t_calcunit calc);
void				limit_plane(t_shape shape, t_ray ray,
		double *t, double dist);

/*
 **	Img file
 */

void				blur_mode(t_env *env, t_point p);
t_color				get_color_pixel(SDL_Surface *surf, t_point p);
void				put_filter(t_all param);
void				img_put_pixel(SDL_Surface *surf, t_point point);
void				refresh_img(t_all *param);

/*
 **	Utils file
 */

double				get_vect_dist(t_vector3d a, t_vector3d b);
double				magnitude(t_vector3d v);

/*
 **	rotate_matrice
 */

t_ray				adapt_ray(t_ray ray, t_mat3d mat);
int					rotate_event(t_all *param, int key);

/*
 **	Camera
 */

t_vector3d			set_axe(int x, int y, t_camera *cam);

/*
 **	Parse
 */

int					parse_old(char *file, t_scene *scene);
void				parse(t_all *param, char *arg);
void				get_scene_infos(t_all *param, int *fd);
void				get_ligths(t_all *param, int *fd);
void				get_objs(t_all *param, int *fd);
void				print_infos(int a, int b);
t_shape				check_obj(t_shape *obj);
t_light				check_light(t_light *spot);

char				*extract_text(char *line);
t_vector3d			extract_vd3(char *line);
int					rt_get_next_line(int fd, char **line);

t_light				cpy_light(char **tab);
void				cpy_cone(t_shape *shape, char **tab);
void				cpy_cylinder(t_shape *shape, char **tab);
void				cpy_sphere(t_shape *shape, char **tab);
void				cpy_plane(t_shape *shape, char **tab);
void				create_scene(char *s, t_scene *scene,
		int *nb_cam, int *nb_lght);
void				ft_abort_free(char *msg, char *line);
void				parsing_quit(char *msg, char **splt_ln, char *ln);

/*
 **	Misc
 */

int					sdl_key(t_all *param, int key);

void				draw_rect(t_vector4d pos, t_color c, SDL_Renderer *rend);
void				put_string(t_label str, t_vector4d pos_p, SDL_Renderer *rend);
void                draw_bloc(t_bloc *bloc, SDL_Renderer *rend);
void				draw_ui(t_all *param);

SDL_Renderer		*surface_2_rend(t_env *env);
void				create_win_render(t_env *env);
void				create_all_surface(t_env *env);
void				clear_render(t_env *env);
void				create_render(t_all *param);
void				quit_exe(t_all param);
void    			init_sdl(void);
int				    new_ui(t_all *param);
void				event_button(t_all *param, int x, int y);

#endif
