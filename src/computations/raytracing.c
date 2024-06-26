/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raytracing.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nsalles <nsalles@student.42perpignan.fr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/18 02:48:37 by nsalles           #+#    #+#             */
/*   Updated: 2024/03/27 20:03:23 by nsalles          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

/*
 *	Launches a ray and returns the color of the first shape encountered, 
 *	black if no shape are encountered.
*/
t_color	launch_ray(t_ray ray, t_objects *objs, int depth)
{
	t_hitinfo	hit;
	t_color		reflection_color;

	hit = ray_intersection(ray, objs);
	if (!hit.did_hit)
		return ((t_color){0, 0, 0});
	hit.reflect = reflect(ray.dir, hit.normal);
	hit.color = compute_lights(objs->alight, objs->lights, &hit, objs);
	if (depth == 1 || hit.reflect_ratio <= 0)
		return (multiplies_color(hit.color, (1 - hit.reflect_ratio)));
	ray.origin = hit.pos;
	ray.dir = hit.reflect;
	reflection_color = launch_ray(ray, objs, depth - 1);
	reflection_color = multiplies_color(reflection_color, 0.95);
	return (combine_colors(hit.color, reflection_color, hit.reflect_ratio));
}

static t_vec	set_ray_dir(t_vec *point, t_vec base[3])
{
	t_vec	dir;

	dir.x = point->x * base[0].x + point->y * -base[1].x
		+ point->z * base[2].x;
	dir.y = point->x * base[0].y + point->y * -base[1].y
		+ point->z * base[2].y;
	dir.z = point->x * base[0].z + point->y * -base[1].z
		+ point->z * base[2].z;
	return (dir);
}

/*
 *	Goes through all the pixels and launch a ray in the direction of the camera
 *	for each of them. Colors the pixel with the color of the first object 
 *	encountered. Designed to work with threads.
*/
void	*draw_screen_with_threads(void *arg)
{
	t_thread_args	*args;
	t_vec			pixel;
	t_ray			ray;
	t_vec			point;
	t_color			pixel_color;

	args = (t_thread_args *)arg;
	pixel.y = args->start_y - 1;
	while (++pixel.y < args->end_y)
	{
		pixel.x = args->start_x - 1;
		while (++pixel.x < args->end_x)
		{
			point = add_vect(args->plane->bottom_left,
					get_vect(args->plane->width * pixel.x
						/ (args->img->width - 1), args->plane->height
						* pixel.y / (args->img->height - 1), 0));
			ray.dir = set_ray_dir(&point, args->cam->base);
			ray.dir = normalize(ray.dir);
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
	t_vec	pixel;
	t_ray	ray;
	t_vec	point;
	t_color	pixel_color;

	pixel.y = -1;
	while (++pixel.y < img->height)
	{
		display_loading("Rendering:", 0, pixel.y + 1,
			(double)img->height / 100);
		pixel.x = -1;
		while (++pixel.x < img->width)
		{
			point = add_vect(plane->bottom_left,
					get_vect(plane->width * pixel.x / (img->width - 1),
						plane->height * pixel.y / (img->height - 1), 0));
			ray.dir = set_ray_dir(&point, cam->base);
			ray.dir = normalize(ray.dir);
			ray.origin = cam->pos;
			pixel_color = launch_ray(ray, objs, REFLECTION_DEPTH);
			pixel_put(img, pixel.x, pixel.y, pixel_color);
		}
	}
}
