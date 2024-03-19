/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minirt.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nsalles <nsalles@student.42perpignan.fr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/15 12:47:05 by nsalles           #+#    #+#             */
/*   Updated: 2024/03/19 02:55:19 by nsalles          ###   ########.fr       */
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
	int	r;
	int	g;
	int	b;
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
    t_color	color;
}	t_alight;

typedef struct s_camera
{
    t_point	pos;
    t_point	dir;
	t_point	dir_x;
	t_point	dir_y;
	t_point	dir_z;
    int		fov;
	double	viewport_dst;
}	t_camera;

typedef struct s_light
{
    t_point	pos;
    double	brightness;
    t_color	color;
}	t_light;

typedef struct s_sphere
{
    t_point	pos;
    double	radius;
    t_color	color;
	double	reflect_ratio;
}	t_sphere;

typedef struct s_plane
{
    t_point	pos;
    t_point	normal;
    t_color	color;
	double	reflect_ratio;
}	t_plane;

typedef struct s_cylinder
{
    t_point	pos;
    t_point	dir;
    double	radius;
    double	height;
    t_color	color;
	double	reflect_ratio;
	t_point	a;
	t_point	b;
	t_point	ba;
	double	baba;

}	t_cylinder; // retirer des valeurs et n'utiliser que a et b ?

typedef struct s_cy_values
{
	int		is_cap;
	t_point oc;
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
    t_alight	*a_light;
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
	t_point	bottom_left;
	double	height;
	double	width;
}	t_viewport_plane;

typedef struct s_hitinfo
{
	int		did_hit;
	t_point	pos;
	double	dst;
	t_color	color;
	t_point	normal;
	double	reflect_ratio;
}	t_hitinfo;

typedef struct s_ray
{
	t_point		origin;
	t_point		dir;
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
t_point		get_point(double x, double y, double z);
t_point		get_point_from_string(char *string, char delimiter);
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
int			is_in_shadow(t_point start_pos, t_point light_dir, double light_dst,
	t_objects *objs);
t_color		apply_light(t_light *light, t_hitinfo *hit, t_objects *objs);

/* COLLISIONS */
t_hitinfo	ray_collision(t_ray ray, t_objects *objs);
void		spheres_collision(t_ray ray, t_sphere **spheres, 
	t_hitinfo *closest_hit);
void		cylinders_collision(t_ray ray, t_cylinder **cylinders, 
	t_hitinfo *closest_hit);
void	planes_collision(t_ray ray, t_plane **planes, 
	t_hitinfo *closest_hit);


/* VECTORS */
double		ft_lenght(t_point vect);
t_point		multiply_vect(t_point vect, double scalar);
t_point		divide_vect(t_point vect, double scalar);
double	    vector_scalar_product(t_point v1, t_point v2);
t_point		soustract_vect(t_point vect1, t_point vect2);
t_point		add_vect(t_point vect1, t_point vect2);
void		normalize_vect(t_point *vect);
t_point		copy_vect(t_point vect);
t_point 	cross_product(t_point vect1, t_point vect2);
double		dot(t_point vect1, t_point vect2);
t_point		get_vect(double x, double y, double z);
void		print_vect(char *msg, t_point vect);
double		ft_random(unsigned int *seed);
t_ray		bounce_ray(t_point dir, t_point normal_dir, t_point hit_pos);

/* DRAWING */
void		pixel_put(t_image *img, int x, int y, t_color color);
void		*draw_screen_with_threads(void *arg);
void		draw_screen(t_camera *cam, t_viewport_plane *plane, t_objects *objs,
	t_image *img);

#endif