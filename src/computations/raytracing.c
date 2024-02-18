/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raytracing.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nsalles <nsalles@student.42perpignan.fr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/18 02:48:37 by nsalles           #+#    #+#             */
/*   Updated: 2024/02/18 17:07:37 by nsalles          ###   ########.fr       */
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
	t_sphere	sph = *data->spheres;

	int	x = -1;
	int	y;
	while (++x < SCREEN_W)
	{
		y = -1;
		while (++y < SCREEN_H)
		{
			ray.x = x;
			ray.y = y;
			ray.z = 0;
			while (++ray.z < 100)
			{
				if (sd_sphere(soustract_vect(ray, *sph.pos), sph.diameter) < 0)
				{
					pixel_put(img, x, y, sph.color);
					break ;
				}
			}
		}
	}
}
