/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minirt.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: drenassi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/15 12:47:05 by nsalles           #+#    #+#             */
/*   Updated: 2024/02/20 14:02:36 by drenassi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINIRT_H
# define MINIRT_H

# include <stdio.h>
# include <math.h>
# include "../libs/libft/includes/libft.h"
# include "../libs/minilibx-linux/mlx.h"

# define SCREEN_H 800
# define SCREEN_W 1200

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
    t_point			*vector;
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

typedef struct s_data
{
    t_alight	*a_light;
    t_camera	*camera;
    t_light		*light;
    t_sphere	*spheres;
    t_plane		*planes;
    t_cylinder	*cylinders;
}	t_data;

typedef struct s_minirt
{
	t_window	*win;
	t_image		*img;
	t_data	    *data;
}	t_minirt;


/* UTILS */
int			ft_strcmp(const char *s1, const char *s2);
double		ft_atod(char *str);
int			double_array_len(char **array);
void		free_double_array(char **array);
int			print_error(char *msg);
int			is_empty(char *line);
/* COLORS UTILS */
int			format_color(char *colors_str);
t_color		int_to_rgb(int color);
int		    rgb_to_int(int r, int g, int b);
void	    protect_colors(t_color *color);
/* PRINT DATAS UTIL */
void	    print_data(t_data data);

/* CHECK CONFIG FILE*/
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
t_window	*get_window(void);
void		destroy_window(t_window *win);
t_image		*get_image(t_window *win);
void		destroy_image(t_image *img, void *mlx);
t_point	    *str_to_point(char *str);
t_point		*set_point(double x, double y, double z);
void		destroy_point(t_point *point);
t_camera	*set_camera(t_point *pos, t_point *direction, int fov);
void		destroy_camera(t_camera *camera);
t_alight	*set_alight(double brightness, int color);
void		destroy_alight(t_alight *alight);
t_light		*set_light(t_point *pos, double ratio, int color);
void		destroy_light(t_light *light);
void    	set_plane(t_plane **plane, t_point *pos, t_point *vector, int color);
void	    destroy_plane(t_plane **plane);
void		set_sphere(t_sphere **sphere, t_point *pos, \
        double radius, int color);
void		destroy_sphere(t_sphere **sphere);
void    	set_cylinder(t_cylinder **cylinder, t_point *pos_vect[2], \
        double rad_height[2], int color);
void		destroy_cylinder(t_cylinder **cylinder);

char		**create_data_array(char *line);
t_data	    *set_data(char *file);
void	    destroy_data(t_data *data);

/* EXIT */
int			exit_handling(t_minirt *data);

/* INPUTS */
int			user_input(int keycode, t_minirt *data);

/* RAYTRACING */
void		raytracing(t_image *img, t_data *data);

/* AMBIENT LIGHTNING */
void	    apply_ambient_lightning(t_data *data);

/* VECTORS */
double		ft_lenght(t_point vect);
void		vect_multiply(t_point *vect, double scalar);
t_point		soustract_vect(t_point vect1, t_point vect2);
void		expand_vect(t_point *vect, t_point normalized_vect);
void		normalize_vect(t_point *vect);
t_point		copy_vect(t_point vect);
void		print_vect(t_point vect);

/* DRAWING */
void		pixel_put(t_image *img, int x, int y, int color);

#endif