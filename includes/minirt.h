/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minirt.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nsalles <nsalles@student.42perpignan.fr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/15 12:47:05 by nsalles           #+#    #+#             */
/*   Updated: 2024/03/20 17:22:16 by nsalles          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINIRT_H
# define MINIRT_H

# include <stdio.h>
# include <math.h>
# include <pthread.h>
# include "../libs/libft/includes/libft.h"
# include "../libs/minilibx-linux/mlx.h"

# define THREADS_GRID_SIZE 6

typedef struct s_window
{
	void	*mlx;
	void	*window;
	int		width;
	int		height;
}		t_window;

typedef struct s_image
{
	void	*image;
	char	*addr;
	int		bits_per_pixel;
	int		line_length;
	int		endian;
	int		width;
	int		height;
	double	aspect_ratio;
}		t_image;

typedef struct s_color
{
	double	r;
	double	g;
	double	b;
}		t_color;

typedef struct s_vec
{
    double	x;
    double	y;
    double	z;
}	t_vec;

typedef struct s_alight
{
    double	ratio;    
    t_color	color;
}	t_alight;

typedef struct s_camera
{
    t_vec	pos;
    t_vec	dir;
	t_vec	dir_x;
	t_vec	dir_y;
	t_vec	dir_z;
    int		fov;
	double	viewport_dst;
}	t_camera;

typedef struct s_light
{
    t_vec	pos;
    double	brightness;
    t_color	color;
}	t_light;

typedef struct s_sphere
{
    t_vec	pos;
    double	radius;
    t_color	color;
	double	reflect_ratio;
	double	specular;
}	t_sphere;

typedef struct s_plane
{
    t_vec	pos;
    t_vec	normal;
    t_color	color;
	double	reflect_ratio;
	double	specular;
}	t_plane;

typedef struct s_cylinder
{
    t_vec	pos;
    t_vec	dir;
    double	radius;
    double	height;
    t_color	color;
	double	reflect_ratio;
	double	specular;
	t_vec	a;
	t_vec	b;
	t_vec	ba;
	double	baba;
}	t_cylinder; // retirer des valeurs et n'utiliser que a et b ?

typedef struct s_cy_values
{
	int		is_cap;
	t_vec oc;
	double	bard;
	double	baoc;
	double	k2;
	double	k1;
	double	k0;
	double	discr;
	double	dst;
	double	y;
}	t_cy_values;

typedef struct s_objects
{
    t_alight	*alight;
    t_camera	*camera;
    t_light		*light;
    t_sphere	**spheres;
    t_plane		**planes;
    t_cylinder	**cylinders;
}	t_objects;

typedef struct s_minirt
{
	t_window	win;
	t_image		img;
	t_objects	objs;
}	t_minirt;

typedef struct	s_viewport_plane
{
	t_vec	bottom_left;
	double	height;
	double	width;
}	t_viewport_plane;

typedef struct s_hitinfo
{
	int		did_hit;
	t_vec	pos;
	double	dst;
	t_color	color;
	t_vec	normal;
	t_vec	reflect;
	double	reflect_ratio;
	double	specular;
}	t_hitinfo;

typedef struct s_ray
{
	t_vec	origin;
	t_vec	dir;
}	t_ray;

typedef struct s_thread_args
{
	t_camera			*cam;
	t_objects			*objs;
	t_image				*img;
	t_viewport_plane	*plane;
	int					start_x;
	int					end_x;
	int					start_y;
	int					end_y;
}	t_thread_args;

/* UTILS */
int			ft_strcmp(const char *s1, const char *s2);
double		ft_atod(char *str);
double		sign(double x); // move function file
int			double_array_len(char **array);
void		free_double_array(char **array);
void		free_triple_array(char ***array);
int			print_error(char *msg);
void		print_usage(void);
int			is_empty(char *line);
char		*readfile(int fd);
int			check_input(int ac, char **av, int *hardware);

/* COLORS UTILS */
t_color		format_color(char *colors_str);
void		display_loading(char *msg, int start, int pos, double percent_size);
t_color		int_to_rgb(int color);
int			color_to_int(t_color color);
void		protect_colors(t_color *color);
t_color		combine_colors(t_color color, t_color reflective, double ratio);
t_color		multiplies_color(t_color color, double factor);

/* CHECK CONFIG FILE*/
char		**create_data_array(char *line);
int			check_file(char *file);
int			check_identifier(char *line);
int			check_double(char *f);
int			check_rgb(char *param);
int			check_coordinates(char *coord);
int			check_orientation_vector(char *coord);
int 		check_ambiant_lightning(char **data);
int			check_camera(char **data);
int	        check_light(char **data);
int	        check_plane(char **data);
int         check_sphere(char **data);
int	        check_cylinder(char **data);

/* INIT STRUCTURES */
t_vec		get_vec(double x, double y, double z);
t_vec		get_vec_from_string(char *string, char delimiter);
int			init_window(t_window *win, int width, int height);
void		destroy_window(t_window *win);
int			get_image(t_image *img, t_window win);
void		destroy_image(t_image *img, void *mlx);
int			get_objects(t_objects *objs, char *filename);
void		destroy_objects(t_objects *objs);
t_alight	*get_alight(char ***objs);
void		destroy_alight(t_alight *alight);
t_camera	*get_camera(char ***objs);
void		destroy_camera(t_camera *camera);
t_light		*get_light(char ***objs);
void		destroy_light(t_light *light);
t_sphere	**get_spheres(char ***objs, int num_objects);
void		destroy_spheres(t_sphere **spheres);
t_cylinder	**get_cylinders(char ***objs, int num_objects);
void		destroy_cylinders(t_cylinder **cylinders);
t_plane		**get_planes(char ***objs, int num_objects);
void		destroy_planes(t_plane **planes);

/* EXIT */
int			exit_handling(t_minirt *data);

/* INPUTS */
int			user_input(int keycode, t_minirt *data);

/* RAYTRACING */
void		render_one_thread(t_minirt *data);
void		render_multiple_threads(t_minirt *data, int grid_size);
t_color		apply_ambient_lightning(t_alight *alight, t_color color);
int			is_in_shadow(t_vec start_pos, t_vec light_dir, double light_dst,
	t_objects *objs);
t_color	apply_light(t_alight *alight, t_light *light, t_hitinfo *hit, 
	t_objects *objs);
/* intersectionS */
t_hitinfo	ray_intersection(t_ray ray, t_objects *objs);
void		spheres_intersection(t_ray ray, t_sphere **spheres, 
	t_hitinfo *closest_hit);
void		cylinders_intersection(t_ray ray, t_cylinder **cylinders, 
	t_hitinfo *closest_hit);
void	planes_intersection(t_ray ray, t_plane **planes, 
	t_hitinfo *closest_hit);


/* VECTORS */
double		ft_lenght(t_vec vect);
t_vec		multiply_vect(t_vec vect, double scalar);
t_vec		divide_vect(t_vec vect, double scalar);
double	    vector_scalar_product(t_vec v1, t_vec v2);
t_vec		soustract_vect(t_vec vect1, t_vec vect2);
t_vec		add_vect(t_vec vect1, t_vec vect2);
t_vec		normalize(t_vec vect);
t_vec		copy_vect(t_vec vect);
t_vec 		cross_product(t_vec vect1, t_vec vect2);
double		dot(t_vec vect1, t_vec vect2);
t_vec		get_vect(double x, double y, double z);
void		print_vect(char *msg, t_vec vect);
t_vec		reflect(t_vec dir, t_vec normal);

/* DRAWING */
void		pixel_put(t_image *img, int x, int y, t_color color);
void		*draw_screen_with_threads(void *arg);
void		draw_screen(t_camera *cam, t_viewport_plane *plane, t_objects *objs,
	t_image *img);

#endif