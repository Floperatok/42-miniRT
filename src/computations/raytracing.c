/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raytracing.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nsalles <nsalles@student.42perpignan.fr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/18 02:48:37 by nsalles           #+#    #+#             */
/*   Updated: 2024/03/04 17:55:02 by nsalles          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"


static void	setup_camera(t_camera *cam)
{
	cam->viewport_dst = 1;
	
	// double	rot = 0.01745329 * 90;

	// cam->dir_x.x = (cam->direction.z * sin(rot)) + (cam->direction.x * cos(rot));
	// cam->dir_x.y = 0;
	// cam->dir_x.z = (cam->direction.z * cos(rot)) - (cam->direction.x * sin(rot));

	/* dont work with rotation such as {1, 0, 0} */
	// cam->dir_y.x = -cam->direction.x;
	// cam->dir_y.y = fmax(cam->direction.x, cam->direction.z);
	// cam->dir_y.z = -cam->direction.y;
	
	// cam->dir_z = cam->direction;

	cam->dir_x = get_vect(1, 0, 0);
	cam->dir_y = get_vect(0, 1, 0);
	cam->dir_z = get_vect(0, 0, 1);
	
	// printf("cam   : x=%f ; y=%f ; z=%f\n\n", cam->direction.x, cam->direction.y, cam->direction.z);
	// printf("dir_x : x=%f ; y=%f ; z=%f\n", cam->dir_x.x, cam->dir_x.y, cam->dir_x.z);
	// printf("dir_y : x=%f ; y=%f ; z=%f\n", cam->dir_y.x, cam->dir_y.y, cam->dir_y.z);
	// printf("dir_z : x=%f ; y=%f ; z=%f\n", cam->dir_z.x, cam->dir_z.y, cam->dir_z.z);
}

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

/*
 *	Launches a ray and returns the color of the first shape encountered, 
 *	black if no shape are encountered.
*/
int	launch_ray(t_ray ray, t_objects *objs)
{
	t_hitinfo hit;
	int	color;

	hit = ray_collision(ray, objs);
	if (!hit.did_hit)
		return (0x000000);
	ray.origin = hit.hit_point;
	ray.dir = soustract_vect(ray.dir, multiply_vect(hit.normal_dir,\
		dot(ray.dir, hit.normal_dir) * 2));
	hit.color = apply_ambient_lightning(objs->a_light, hit.color);
	color = apply_light(objs->light, &hit);
	return(color);
}

/*
 *	Goes through all the pixels and launch a ray in the direction of the camera
 *	for each of them. Colors the pixel with the color of the first object 
 *	encountered.
*/
void	camera_ray(t_camera *cam, t_viewport_plane *plane, t_objects *objs,
	t_image *img)
{
	t_point	pixel;
	t_ray	ray;
	t_point	point;

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
			ray.dir.x = point.x * cam->dir_x.x + point.y * -cam->dir_y.x + point.z * cam->dir_z.x;
			ray.dir.y = point.x * cam->dir_x.y + point.y * -cam->dir_y.y + point.z * cam->dir_z.y;
			ray.dir.z = point.x * cam->dir_x.z + point.y * -cam->dir_y.z + point.z * cam->dir_z.z;
			normalize_vect(&ray.dir);
			ray.origin = cam->pos;
			pixel_put(img, pixel.x, pixel.y, launch_ray(ray, objs));
		}
	}
}

void	render(t_objects *objs, t_image *img, t_window *win)
{
	t_viewport_plane plane;

	setup_camera(objs->camera);
	plane = set_viewport_plane(objs->camera, img);
	camera_ray(objs->camera, &plane, objs, img);
	mlx_put_image_to_window(win->mlx, win->window, img->image, 0, 0);
}