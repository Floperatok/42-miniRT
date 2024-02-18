/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raytracing.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nsalles <nsalles@student.42perpignan.fr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/18 02:48:37 by nsalles           #+#    #+#             */
/*   Updated: 2024/02/18 19:25:05 by nsalles          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

double	sd_sphere(t_point vect, double radius)
{
	return (ft_lenght(vect) - radius);
}

void	raytracing(t_image *img, t_data *data)
{
	t_point		ray;
	t_point		normalized;
	t_camera	cam = *data->camera;
	t_sphere	sph = *data->spheres;

	//	Shifting the camera pos to the center of the screen
	cam.pos->x += SCREEN_W / 2;
	cam.pos->y += SCREEN_H / 2;

	int	x;
	int	y = -(SCREEN_H / 2);

	//	Loading display
	int			percentage = SCREEN_H / 100;
	int			counter = 0;
	ft_printf("Rendering:\t0%%");

	while (y < SCREEN_H / 2)
	{
		//	Loading update
		if (counter % percentage == 0)
			ft_printf("\b\b\b\b\t%d%%", counter / percentage);
		counter++;
		
		x = -(SCREEN_W / 2);
		while (x < SCREEN_W / 2)
		{
			ray.x = x;
			ray.y = y;
			ray.z = 500; // distance between the camera and the viewport pixels
			normalize_vect(&ray);
			normalized = copy_vect(ray);
			while (ray.z < 100)
			{
				expand_vect(&ray, normalized); // expand the ray step by step until a shape is found
				if (sd_sphere(soustract_vect(ray, *sph.pos), sph.diameter) < 0)
				{
					// if a shape is found, put a pixel of the color of the shape
					pixel_put(img, x + cam.pos->x, y + cam.pos->y, sph.color);
					break ;
				}
			}
			x++;
		}
		y++;
	}
	ft_printf("\b\b\b\b\t100%%\n");
}
