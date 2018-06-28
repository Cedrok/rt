/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rt.h                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cpieri <cpieri@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/18 17:15:16 by tmilon            #+#    #+#             */
/*   Updated: 2018/06/28 14:34:47 by cvautrai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RT_H
# define RT_H

# include <SDL.h>
# include <SDL_ttf.h>
# include <SDL_image.h>
# include "../libgraph/include/libgraph.h"
# include "../libft/include/libft.h"

/*
 ******************************* Disp defines *********************************
*/

# define W_WIDTH			1280
# define W_HEIGHT			720
# define DIST_MAX			2000000
# define DIST_MIN			0.00000001
# define THREAD_LIMIT		8
# define PI					3.141592653
# define MOVE				0.1f

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
 ******************************* Item defines *********************************
*/

# define PATH1				"scenes/scene_1.txt"
# define PATH2				"scenes/scene_2.txt"
# define PATH3				"scenes/scene_3.txt"

/*
** Basic structs
*/

typedef struct		s_point
{
	int				x;
	int				y;
	int				color;
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

typedef struct		s_shadunit
{
	int				shad_color;
	double			actual_dist;
	int				actual_id;
}					t_shadunit;

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
	int				is_hidden;
}					t_light;

typedef struct		s_textunit
{
	int				has_texture;
	double			has_rainbow;
	double			has_checker;
	double			has_waves;
	int				*texture;
	int				texture_width;
	double			x_scale;
	double			y_scale;
	double			x_offset;
	double			y_offset;
}					t_textunit;

typedef struct		s_limunit
{
	t_vector3d		cut_amount;
	double			cut_radius;
}					t_limunit;

typedef struct		s_shape
{
	int				id;
	int				type;
	int				color;
	int				base_color;
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
	int				normal_dir;
	double			maxdist;
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
** Structs for Perlin's noise
*/

typedef struct		s_perlin_stuff
{
	int				*permutation;
	t_vector2d		*grad_tab;
	double			a;
	double			b;
	double			c;
	double			d;
	t_vector2d		grad_a;
	t_vector2d		grad_b;
	t_vector2d		grad_c;
	t_vector2d		grad_d;
}					t_perlin_stuff;

/*
**	Struct for ui
*/

typedef struct		s_left
{
	t_label			*trot;
	t_label			*tran;
	t_button		*rot_0;
	t_button		*rot_1;
	t_button		*rot_2;
	t_button		*rot_3;
	t_button		*rot_4;
	t_button		*rot_5;
	t_button		*mv_0;
	t_button		*mv_1;
	t_button		*mv_2;
	t_button		*mv_3;
	t_button		*mv_4;
	t_button		*mv_5;
	t_button		*dsel;
	t_button		*del;
}					t_left;

typedef struct		s_center
{
	t_button		*btn_sph;
	t_button		*btn_cyl;
	t_button		*btn_pla;
	t_button		*btn_cne;
	t_button		*btn_lgt;
}					t_center;

typedef struct		s_right
{
	t_button		*btn_sepia;
	t_button		*btn_gray;
	t_button		*btn_neg;
	t_button		*btn_def;
	t_button		*btn_cart;
	t_button		*btn_alias;
	t_label			*opt;
	t_button		*btn_shot;
	t_button		*btn_fst;
	t_button		*btn_sc1;
	t_button		*btn_sc2;
	t_button		*btn_sc3;
}					t_right;

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
	int				g_id;
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
	double			move;
}					t_all;

/*
** Thread building struct
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

t_ray				new_ray(t_vector3d o, t_vector3d d);
t_point				new_point(int x, int y, int color);
t_camera			new_cam(t_vector3d orig, t_vector3d rot);
void				new_shape(void *p, int type);
t_shape				default_shape(int i);
void				new_spot(void *p, int c);
t_light				default_light(void);

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
t_vector3d			cylinder_normal(t_shape shape,
												t_vector3d intersection_point);
t_vector3d			cone_normal(t_shape shape, t_vector3d intersection_point);

/*
** Display functs
*/

int					transparency(t_all *param, t_ray ray, int fastmode);
int					shadow_transp(t_all *param, t_ray ray, int start_color);
int					set_color(t_all *param, t_intersect intersection);
double				get_nearest_intersection(t_ray *ray, t_scene scene,
				t_intersect *nearest_intersect, double maxdist);
void				setup_multithread(t_all param);
void				fastmode_complete(t_all *param);

/*
** Texture
*/

t_shape				texture(t_intersect *i, t_shape s, int normal_dir);
void				setup_textunit(const char *surfpath, t_textunit *textunit);
void				get_uv_mapping_coord(double *u, double *v,
										t_intersect i, t_shape s);
t_vector3d			bump_mapping(t_vector3d normal, int colorint);

/*
** Limiters
*/

void				limit_sphere(t_shape shape, t_ray ray,
		double *t, t_calcunit calc);
void				limit_cylinder(t_shape shape, t_ray ray,
		double *t, t_calcunit calc);
void				limit_cone(t_shape shape, t_ray ray,
		double *t, t_calcunit calc);
void				limit_plane(t_shape shape, t_ray ray,
		double *t, double dist);

/*
**	Is in checker
*/

void				is_light_in(t_list *light_lst, t_list *shape_lst);
int					is_in_sphere(t_shape sphere, t_light light);
int					is_in_cylinder(t_shape cyl, t_light light);
int					is_in_cone(t_shape cone, t_light light);
int					is_in_plane(t_shape plane, t_light light);

/*
**	Img & SDL func
*/

t_color				get_color_pixel(SDL_Surface *surf, t_point p);
void				put_filter(t_all param);
void				blur_mode(t_env *env, t_point point);
double				cartoon(double intensity);
void				img_put_pixel(SDL_Surface *surf, t_point point);
void				refresh_img(t_all *param);
int					sdl_key(t_all *param, int key);
void				refresh_surf(void *delay, int type);
void				init_sdl(void);
void				create_win_render(t_env *env);
void				create_all_surface(t_env *env);
void				clear_render(t_env *env);
void				create_render(t_all *param);

/*
**	UI func
*/

int					new_ui(t_all *param);
t_bloc				*create_bloc_filter(int w, int h);
t_bloc				*create_bloc_left(int w, int h);
void				event_button(t_all *param, int x, int y);
void				del_shape(void *p, int type);
void				btn_fastmode(void *p, int type);
void				dselect(void *p, int type);
t_vector4d			size_rend(int w, int h);
void				delshape_func(void *ptr, size_t ok);
void				free_ui(t_all *param);
void				draw_rect(t_vector4d pos, t_color c, SDL_Renderer *rend);
void				put_string(t_label *str, t_vector4d pos_p,
				SDL_Renderer *rend);
void				draw_bloc(t_bloc *bloc, SDL_Renderer *rend);
void				draw_ui(t_all *param);
void				setf_btn_r(t_bloc *bc);
void				setf_btn_c(t_bloc *bc);
void				setf_btn_l(t_bloc *bc);
void				select_shape(t_all *param, int x, int y);
void				cartoon_mode(void *p, int type);
void				move_shape(void *p, int type);
void				rot_shape(void *p, int type);
t_shape				*get_shape_with_id(int id, t_scene sc);
SDL_Renderer		*surface_2_rend(t_env *env);
void				color_btn_mv(t_bloc *bc);

/*
**	Utils func
*/

t_vector3d			normals(t_shape shape, t_vector3d point);
int					collisions(t_shape shape, t_ray ray, double *t);
int					is_in(t_shape shape, t_light light);
void				int_array_to_surf(SDL_Surface *surf, int *colorarray);

/*
**	Perlin's  noise
*/

void				perlin_init(t_perlin_stuff *perlin);
int					**perlin_tab_init(void);
int					*perlin_texture(double res_x,
									double res_yi, int limit);
/*
**	rotate_matrice
*/

t_ray				adapt_ray(t_ray ray, t_mat3d mat);
int					rotate_event(t_all *param, int key);

/*
**	Camera
*/

t_vector3d			set_axe(int x, int y, t_camera *cam, SDL_Surface *surf);
t_camera			update_cam(t_all *param);
void				move_forward(t_camera *cam, double move, int sign);
void				move_rightward(t_camera *cam, double move, int sign);
void				move_upward(t_camera *cam, double move, int sign);

/*
**	Parse
*/

void				parse(t_all *param, char *arg, int *reset);
void				get_scene_infos(t_all *param, int *fd);
void				get_ligths(t_all *param, int *fd);
void				get_objs(t_all *param, int *fd);
void				grab_obj(t_scene *scene, int *fd);
void				grab_texture(t_shape *obj, int *fd);
void				grab_cut(t_shape *obj, int *fd);
void				print_infos(int a, int b);
t_shape				check_obj(t_shape *obj);
t_light				check_light(t_light *spot);
char				*extract_text(char *line);
t_vector3d			extract_vd3(char *line);
int					rt_get_next_line(int fd, char **line);
void				end_lst(t_scene *scene);
void				ft_abort_free(char *msg, char *line);

/*
**	Misc
*/

void				screenshot(void *p, int c);
void				change_scene(void *p, int key);
void				quit_exe(t_all param);

#endif
