/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raytracing.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: drenassi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/18 02:48:37 by nsalles           #+#    #+#             */
/*   Updated: 2024/02/22 11:48:56 by drenassi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

// double	farest_obj_distance(t_data *data)
// {
// 	// placeholder
// 	return fmax(get_vect_norm(*data->spheres->pos) + data->spheres->radius,
// 		get_vect_norm(*data->spheres->next->pos) + data->spheres->next->radius);
// }

// t_values	compute_values(t_data *data)
// {
// 	t_values	values;

// 	values.farest_obj = farest_obj_distance(data);
// 	values.half_screen_h = SCREEN_H / 2;
// 	values.half_screen_w = SCREEN_W / 2;
// 	values.viewport_dist = VIEWPORT_DIST // change to takes fov as input
// 	values.
// }

/*
 *	Computes and returns the ray vector for the corresponding screen pixel.
*/
 // je ne sais pas si c'est get_ray ou set_ray je te laisse choisir
// t_point	set_ray(t_point pixel, t_point cam_direction)
// {
// 	t_point	ray;
// 	int	half_screen_h;
// 	int	half_screen_w;

// 	half_screen_h = SCREEN_H / 2;
// 	half_screen_w = SCREEN_W / 2;

// 	ray.x = (pixel.x - half_screen_w) / half_screen_w;
// 	ray.y = (pixel.y - half_screen_h) / half_screen_h;
// 	ray.z = 1;

// 	ray.y = (ray.y * cos(cam_direction.x)) - (ray.z * sin(cam_direction.x));
// 	ray.z = (ray.y * sin(cam_direction.x)) + (ray.z * cos(cam_direction.x));
// 	ray.x = (ray.z * sin(cam_direction.y)) + (ray.x * cos(cam_direction.y));
// 	ray.z = (ray.z * cos(cam_direction.y)) - (ray.x * sin(cam_direction.y));
// 	ray.x = (ray.x * cos(cam_direction.x)) - (ray.y * sin(cam_direction.x));
// 	ray.y = (ray.x * sin(cam_direction.x)) + (ray.y * cos(cam_direction.x));
// 	return (ray);
// }

// void	raytracing(t_data *data, t_image *img)
// {
// 	t_point	pixel;
// 	t_point	ray;
// 	t_point	normalized;
// 	double	distance[2];
// 	double	farest_obj;

// 	farest_obj = farest_obj_distance(data);
// 	pixel.y = -1;
// 	while (++pixel.y < SCREEN_H)
// 	{
// 		display_loading("Rendering:", 0, pixel.y + 1, SCREEN_H / 100);
// 		pixel.x = -1;
// 		while (++pixel.x < SCREEN_W)
// 		{
// 			ray = set_ray(pixel, *data->camera->direction);
// 			normalized = ray;
// 			distance[0] = 0;
// 			distance[1] = 0;
// 			while (distance[0] != -1 && distance[1] < farest_obj)
// 			{
// 				distance[0] = detect_shapes(data, img, &ray, &pixel); // should return -1 if no shape are found
// 				distance[1] += distance[0] + 1;
// 				ray = add_vect(ray, multiply_vect(normalized, distance[0] + 1));
// 			}
// 		}
// 	}
// }

/*
void	legacy(t_image *img, t_data *data)
{
	// clean screen for next frame; one pixel is 4 bits.
	ft_bzero(img->addr, 4 * SCREEN_H * SCREEN_W);

	t_point		ray;
	t_point		normalized;
	t_camera	cam = *data->camera;
	//	spheres initializations
	t_sphere	sph = *data->spheres;
	t_sphere	sph2 = *data->spheres->next;

	//	Shifting the camera pos to the center of the screen
	cam.pos->x += SCREEN_W / 2;
	cam.pos->y += SCREEN_H / 2;
	double	farest_obj = get_vect_norm(*sph.pos) + sph.diameter;
	double	distance;
	double	distance2;
	double	min_dist;

	int	x;
	int	y = -(SCREEN_H / 2);
	int	ray_step;

	//	Progress display setup
	int			percentage = SCREEN_H / 100;
	int			counter = 0;
	ft_printf("Rendering:\t0%%");

	while (y < SCREEN_H / 2)
	{
		//	Progress display update
		if (counter % percentage == 0)
			ft_printf("\b\b\b\b\t%d%%", counter / percentage);
		counter++;
		
		x = -(SCREEN_W / 2);
		while (x < SCREEN_W / 2)
		{
			ray.x = x;
			ray.y = y;
			ray.z = 500; // distance between the camera and the viewport pixels
			ray_step = 0;							// affecting the fov
			normalize_vect(&ray);
			normalized = copy_vect(ray);
			while (ray_step < farest_obj)
			{
				ray_step++;
				add_vect(&ray, normalized); // expand the ray step by step until a shape is found
				distance = sd_sphere(substract_vect(ray, *sph.pos), sph.diameter);
				distance2 = sd_sphere(substract_vect(ray, *sph2.pos), sph2.diameter);
				min_dist = fmin(distance, distance2);
				if (distance < 0 && distance <= distance2)
				{
					// if a shape is found, put a pixel of the color of the shape
					pixel_put(img, x + cam.pos->x, y + cam.pos->y, sph.color);
					break ;
				}
				if (distance2 < 0 && distance2 <= distance)
				{
					pixel_put(img, x + cam.pos->x, y + cam.pos->y, sph2.color);
					break ;
				}
				// move the vector forward by the distance of the closest object
				ray.x += normalized.x * min_dist;
				ray.y += normalized.y * min_dist;
				ray.z += normalized.z * min_dist;
				ray_step += min_dist;
			}
			x++;
		}
		y++;
	}
	ft_printf("\b\b\b\b\t100%%\n");
}
*/