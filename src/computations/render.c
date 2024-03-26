/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nsalles <nsalles@student.42perpignan.fr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/12 15:54:59 by nsalles           #+#    #+#             */
/*   Updated: 2024/03/26 15:31:57 by nsalles          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

/*
 *	Computes the position and the sizes of the viewport plane where all the
 *	rays will be launched. These values are calculated from fov and 
 *	screen dimensions.
*/
static t_viewport_plane	set_viewport_plane(t_camera *cam, t_image *img)
{
	t_viewport_plane plane;

	plane.height = cam->viewport_dst * tan(cam->fov * 0.01745329 / 2) * 2;
	plane.width = plane.height * img->aspect_ratio;
	plane.bottom_left = get_vect(-plane.width / 2, -plane.height / 2,\
		cam->viewport_dst);
	return (plane);
}

static t_thread_args	set_args(t_minirt *data, t_viewport_plane *plane, 
	int grid_size, int i)
{
	t_thread_args	args;

	args.cam = data->objs.camera;
	args.plane = plane;
	args.img = &data->img;
	args.objs = &data->objs;
	args.start_x = (data->img.width / grid_size) * (i % grid_size);
	args.end_x = (data->img.width / grid_size) * ((i % grid_size) + 1);
	args.start_y = (data->img.height / grid_size) * (i / grid_size);
	args.end_y = (data->img.height / grid_size) * ((i / grid_size) + 1) + 2;
	return (args);
}

void	render_multiple_threads(t_minirt *data, int grid_size)
{
	t_viewport_plane	plane;
	pthread_t			*threads;
	t_thread_args		*args;
	int					i;

	threads = malloc(sizeof(pthread_t) * (grid_size * grid_size));
	args = malloc(sizeof(t_thread_args) * (grid_size * grid_size));
	setup_camera(data->objs.camera);
	plane = set_viewport_plane(data->objs.camera, &data->img);
	i = -1;
	while (++i < (grid_size * grid_size))
		args[i] = set_args(data, &plane, grid_size, i);
	while (--i >= 0)
		if (pthread_create(&threads[i], NULL, &draw_screen_with_threads, &(args[i])))
			perror("");
	while (++i < (grid_size * grid_size))
		pthread_join(threads[i], NULL);
	mlx_put_image_to_window(data->win.mlx, data->win.window, \
		data->img.image, 0, 0);
	free(threads);
	free(args);
}

void	render_one_thread(t_minirt *data)
{
	t_viewport_plane plane;

	setup_camera(data->objs.camera);
	plane = set_viewport_plane(data->objs.camera, &data->img);
	draw_screen(data->objs.camera, &plane, &data->objs, &data->img);
	mlx_put_image_to_window(data->win.mlx, data->win.window, data->img.image, 0, 0);
}
