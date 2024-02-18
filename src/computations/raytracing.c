/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raytracing.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nsalles <nsalles@student.42perpignan.fr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/18 02:48:37 by nsalles           #+#    #+#             */
/*   Updated: 2024/02/18 18:24:08 by nsalles          ###   ########.fr       */
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
	int			percentage = SCREEN_W / 100;

	int	x = -1;
	int	y;

	ft_printf("Rendering:\t0%%");
	while (++x < SCREEN_W)
	{
		if (x % percentage == 0)
			ft_printf("\b\b\b\b\t%d%%", x / percentage);
		y = -1;
		while (++y < SCREEN_H)
		{
			ray.x = x;
			ray.y = y;
			ray.z = 1;
			while (++ray.z < 100)
			{
				if (sd_sphere(soustract_vect(ray, *sph.pos), sph.diameter) < 0)
				{
					pixel_put(img, x, y, sph.color);
					break ;
				}
				else
					pixel_put(img, x, y, 0x005533);
			}
		}
	}
	ft_printf("\b\b\b\b\t100%%\n");
}
