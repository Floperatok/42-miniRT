/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raytracing.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nsalles <nsalles@student.42perpignan.fr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/18 02:48:37 by nsalles           #+#    #+#             */
/*   Updated: 2024/03/12 17:13:56 by nsalles          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

# define REFLECTION_DEPTH 2

/*
 *	Launches a ray and returns the color of the first shape encountered, 
 *	black if no shape are encountered.
*/
t_color	launch_ray(t_ray ray, t_objects *objs, int depth)
{
	t_hitinfo	hit;
	t_color		reflection_color;

	hit = ray_collision(ray, objs);
	if (!hit.did_hit)
		return ((t_color){0, 0, 0});
	hit.color = apply_ambient_lightning(objs->a_light, hit.color);
	hit.color = apply_light(objs->light, &hit, objs);
	if (depth == 1 || hit.reflect_ratio <= 0)
		return (multiplies_color(hit.color, (1 - hit.reflect_ratio)));
	ray.origin = hit.hit_point;
	ray = bounce_ray(ray.dir, hit.normal_dir, hit.hit_point);
	reflection_color = launch_ray(ray, objs, depth - 1);
	return (combine_colors(hit.color, reflection_color, hit.reflect_ratio));
}

/*
 *	Goes through all the pixels and launch a ray in the direction of the camera
 *	for each of them. Colors the pixel with the color of the first object 
 *	encountered. Designed to work with threads.
*/
void	*draw_screen_with_threads(void *arg)
{
	t_thread_args *args;
	t_point	pixel;
	t_ray	ray;
	t_point	point;
	t_color	pixel_color;

	args = (t_thread_args *)arg;
	pixel.y = args->start_y - 1;
	while (++pixel.y < args->end_y)
	{
		// display_loading("Rendering:", 0, pixel.y + 1, (double)args->img->height / 100);
		pixel.x = args->start_x - 1;
		while (++pixel.x < args->end_x)
		{
			point = add_vect(args->plane->bottom_left, get_vect(args->plane->width * pixel.x / (args->img->width - 1), args->plane->height * pixel.y / (args->img->height - 1), 0));
			ray.dir.x = point.x * args->cam->dir_x.x + point.y * -args->cam->dir_y.x + point.z * args->cam->dir_z.x;
			ray.dir.y = point.x * args->cam->dir_x.y + point.y * -args->cam->dir_y.y + point.z * args->cam->dir_z.y;
			ray.dir.z = point.x * args->cam->dir_x.z + point.y * -args->cam->dir_y.z + point.z * args->cam->dir_z.z;
			// normalize_vect(&ray.dir);
			ray.origin = args->cam->pos;
			pixel_color = launch_ray(ray, args->objs, REFLECTION_DEPTH);
			pixel_put(args->img, pixel.x, pixel.y, pixel_color);
		}
	}
	return (NULL);
}

/*
 *	Goes through all the pixels and launch a ray in the direction of the camera
 *	for each of them. Colors the pixel with the color of the first object 
 *	encountered.
*/
void	draw_screen(t_camera *cam, t_viewport_plane *plane, t_objects *objs,
	t_image *img)
{
	t_point	pixel;
	t_ray	ray;
	t_point	point;
	t_color	pixel_color;

	pixel.y = -1;
	while (++pixel.y < img->height)
	{
		display_loading("Rendering:", 0, pixel.y + 1, (double)img->height / 100);
		pixel.x = -1;
		while (++pixel.x < img->width)
		{
			point = add_vect(plane->bottom_left, 
				get_vect(plane->width * pixel.x / (img->width - 1), 
				plane->height * pixel.y / (img->height - 1), 0));
			// print_vect("", plane->bottom_left);<
			ray.dir.x = point.x * cam->dir_x.x + point.y * -cam->dir_y.x + point.z * cam->dir_z.x;
			ray.dir.y = point.x * cam->dir_x.y + point.y * -cam->dir_y.y + point.z * cam->dir_z.y;
			ray.dir.z = point.x * cam->dir_x.z + point.y * -cam->dir_y.z + point.z * cam->dir_z.z;
			// normalize_vect(&ray.dir);
			ray.origin = cam->pos;
			pixel_color = launch_ray(ray, objs, REFLECTION_DEPTH);
			pixel_put(img, pixel.x, pixel.y, pixel_color);
		}
	}
}
