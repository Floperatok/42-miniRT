/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minirt.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: drenassi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/15 12:47:05 by nsalles           #+#    #+#             */
/*   Updated: 2024/02/22 12:05:35 by drenassi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#ifndef MINIRT_H
# define MINIRT_H

# include <stdio.h>
# include <math.h>
# include "../libs/libft/includes/libft.h"
# include "../libs/minilibx-linux/mlx.h"

# define SCREEN_H 800
# define SCREEN_W 1500
# define VIEWPORT_DIST 500
# define MAX_RAY_DEPTH 3
# define PRECISION 0.001

typedef struct s_window
{
	void	*mlx;
	void	*window;
}		t_window;

typedef struct s_image
{
	void	*image;
	char	*addr;
	int		bits_per_pixel;
	int		line_length;
	int		endian;
}		t_image;

typedef struct s_color
{
	int	r;
	int	g;
	int	b;
    int sum;
}		t_color;

typedef struct s_point
{
    double	x;
    double	y;
    double	z;
}	t_point;

typedef struct s_alight
{
    double	ratio;    
    int		color;
}	t_alight;

typedef struct s_camera
{
    t_point	*pos;
    t_point	*direction;
    int		fov;
}	t_camera;

typedef struct s_viewport
{
	double	w;
	double	w_ratio;
	double	h;
	double	h_ratio;
}	t_viewport;

typedef struct s_light
{
    t_point	*pos;
    double	brightness;
    int		color;
}	t_light;

typedef struct s_sphere
{
    t_point			*pos;
    double			radius;
    int				color;
    struct s_sphere *next;
}	t_sphere;

typedef struct s_plane
{
    t_point			*pos;
    t_point			*normal;
    int				color;
	struct s_plane	*next;
}	t_plane;

typedef struct s_cylinder
{
    t_point				*pos;
    t_point				*vector;
    double				radius;
    double				height;
    int					color;
	struct s_cylinder	*next;
}	t_cylinder;

typedef struct s_obj
{
	t_plane			*pl;
	t_sphere		*sp;
	t_cylinder		*cy;
	struct s_obj	*next;
}	t_obj;

typedef struct s_closest_obj
{
	t_obj	*obj;
	double	distance;
}	t_closest_obj;

typedef struct s_ray
{
	t_point	origin;
	t_point	dir;
	int		depth;
}	t_ray;

typedef struct s_data
{
    t_alight	*a_light;
    t_camera	*camera;
    t_light		*light;
    t_sphere	*spheres;
    t_plane		*planes;
    t_obj       *objs;
    t_cylinder	*cylinders;
}	t_data;

typedef struct s_minirt
{
	t_window	*win;
	t_image		*img;
	t_data	    *data;
}	t_minirt;

typedef struct s_values
{
	double	farest_obj;
	int		half_screen_h;
	int		half_screen_w;
}	t_values;

/* UTILS */
int				ft_strcmp(const char *s1, const char *s2);
double			ft_atod(char *str);
int				double_array_len(char **array);
void			free_double_array(char **array);
int				print_error(char *msg);
int				is_empty(char *line);
/* MATHS UTILS */
t_point			copy_vect(t_point vect);
void			print_vect(t_point vect);
double			get_vect_norm(t_point vect);
t_point			normalize_vect(t_point vect);
t_point			add_vect(t_point vect1, t_point vect2);
t_point			substract_vect(t_point vect1, t_point vect2);
t_point			multiply_vect(t_point vect, double scalar);
double			vector_scalar_product(t_point v1, t_point v2);
t_point			vector_cross_product(t_point v1, t_point v2);
double			vector_cos(t_point v1, t_point v2);
double			vector_sin(t_point v1, t_point v2);
t_point			rotate_vector(t_point vector, t_point axis, \
		double cos, double sin);
void			rotate_base(t_point base[3], t_point direction);
double			quadratic_min(double a, double b, double c, double min);
/* COLORS UTILS */
int				format_color(char *colors_str);
void			display_loading(char *msg, int start, int pos, \
		int percent_size);
t_color			int_to_rgb(int color);
int				rgb_to_int(int r, int g, int b);
void			protect_colors(t_color *color);
/* PRINT DATAS UTIL */
void			print_data(t_data data);

/* CHECK CONFIG FILE*/
int				check_file(char *file);
int				check_identifier(char *line);
int				check_double(char *f);
int				check_rgb(char *param);
int				check_coordinates(char *coord);
int				check_orientation_vector(char *coord);
int 			check_ambiant_lightning(char **data);
int				check_camera(char **data);
int	        	check_light(char **data);
int	        	check_plane(char **data);
int         	check_sphere(char **data);
int	        	check_cylinder(char **data);

/* INIT STRUCTURES */
t_window		*get_window(void);
void			destroy_window(t_window *win);
t_image			*get_image(t_window *win);
void			destroy_image(t_image *img, void *mlx);
t_point	    	*str_to_point(char *str);
t_point			*set_point(double x, double y, double z);
void			destroy_point(t_point *point);
t_camera		*set_camera(t_point *pos, t_point *direction, int fov);
void			destroy_camera(t_camera *camera);
t_viewport		init_viewport(double fov, double distance);
t_alight		*set_alight(double brightness, int color);
void			destroy_alight(t_alight *alight);
t_light			*set_light(t_point *pos, double ratio, int color);
void			destroy_light(t_light *light);
void    		set_plane(t_plane **plane, t_point *pos, \
		t_point *vector, int color);
void	    	destroy_plane(t_plane **plane);
void			set_sphere(t_sphere **sphere, t_point *pos, \
        double radius, int color);
void			destroy_sphere(t_sphere **sphere);
void    		set_cylinder(t_cylinder **cylinder, t_point *pos_vect[2], \
        double rad_height[2], int color);
void			destroy_cylinder(t_cylinder **cylinder);
void			init_objs(t_data *data);
void			set_objs(t_obj **objs, t_plane *pl, t_sphere *sp, \
		t_cylinder *cy);
void			destroy_objs(t_obj **obj);
void			init_ray(t_data *data, t_ray *ray);

char			**create_data_array(char *line);
t_data			*set_data(char *file);
void			destroy_data(t_data *data);

/* EXIT */
int				exit_handling(t_minirt *data);

/* INPUTS */
int				user_input(int keycode, t_minirt *data);

/* RAYTRACING */
// void		render(t_minirt *mem);
// void		raytracing(t_data *data, t_image *img);
// double		detect_shapes(t_data *data, t_image *img, t_point *ray, t_point *pixel);
// double	    sd_sphere(t_point vect, double radius);
t_point			get_obj_normal(t_obj *obj, t_point intersection, t_point dir);
t_point			set_ray(t_point base[3], double x, double y, double z);
t_point			intersection_point(t_ray ray, double distance);
t_closest_obj	closest_intersection(t_ray ray, t_obj *objs);
t_color			ray_trace(t_data *data, t_ray ray, int depth);

/* LIGHTS */
t_color			get_obj_color(t_obj *obj);
t_point			light_intensity(t_data *data);
t_point			reflection_dir(t_point normal, t_point dir);
t_color			reflection_color(t_color color, t_color reflective, \
		double ratio);
t_color			apply_light(t_data *data, t_closest_obj closest);

/* RENDERING */
void			rendering(t_minirt *mem);

/* AMBIENT LIGHTNING */
void			apply_ambient_lightning(t_data *data);

/* DRAWING */
void			draw_pixels(t_image *img, int x, int y, int color);


/* TEST BROUILLON 2 */

#endif