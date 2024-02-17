/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minirt.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: drenassi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/15 12:47:05 by nsalles           #+#    #+#             */
/*   Updated: 2024/02/17 20:48:40 by drenassi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINIRT_H
# define MINIRT_H

# include <stdio.h>
# include <math.h>
# include "../libs/libft/includes/libft.h"
# include "../libs/minilibx-linux/mlx.h"

# define SCREEN_H 700
# define SCREEN_W 700

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

typedef struct s_point
{
    float	x;
    float	y;
    float	z;
}	t_point;

typedef struct s_alight
{
    float	brightness;    
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
    float	brightness;
    int		color;
}	t_light;

typedef struct s_sphere
{
    t_point			*pos;
    float			diameter;
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
    t_point	*pos;
    t_point	*vector;
    float	diameter;
    float	height;
    int		color;
}	t_cylinder;

typedef struct s_data
{
    t_alight	*a_lights;
    t_camera	*cameras;
    t_light		*light;
    t_sphere	*spheres;
    t_plane		*planes;
    t_cylinder	*cylinders;
}	t_data;

typedef struct s_minirt
{
	t_window	*win;
	t_image		*img;
	t_data	*shapes;
}	t_minirt;

/* UTILS */
int			ft_strcmp(const char *s1, const char *s2);
float		ft_atof(char *str);
int			double_array_len(char **array);
void		free_double_array(char **array);
int			print_error(char *msg);
int			is_empty(char *line);
int			format_color(char *colors_str);

/* CHECK CONFIG FILE*/
int			check_file(char *file);
int			check_identifier(char *line);
int			check_float(char *f);
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
t_point		*set_point(float x, float y, float z);
void		destroy_point(t_point *point);
t_camera	*set_camera(t_point *pos, t_point *direction, int fov);
void		destroy_camera(t_camera *camera);
t_alight	*set_alight(float brightness, int color);
void		destroy_alight(t_alight *alight);
t_plane		*set_plane(t_point *pos, t_point *vector, int color);
void		destroy_plane(t_plane *plane);
t_light		*set_light(t_point *pos, float brightness, int color);
void		destroy_light(t_light *light);
t_sphere	*set_sphere(t_point *pos, float diameter, int color);
void		destroy_sphere(t_sphere *sphere);
t_cylinder	*set_cylinder(t_point *pos, t_point *vector, float diameter,\
	float height, int color);
void		destroy_cylinder(t_cylinder *cylinder);

char		**create_data_array(char *line);

/* EXIT */
int			exit_handling(t_minirt *data);

/* INPUTS */
int			user_input(int keycode, t_minirt *data);

/* DRAWING */
void		pixel_put(t_image *img, int x, int y, int color);
void		draw_sphere(t_sphere *sphere, t_camera *cam, t_image *img);
void		draw_image(void *args, t_image *img);

#endif