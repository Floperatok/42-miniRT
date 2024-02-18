/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raytracing.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nsalles <nsalles@student.42perpignan.fr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/18 02:48:37 by nsalles           #+#    #+#             */
/*   Updated: 2024/02/18 04:19:34 by nsalles          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

double	sd_sphere(t_point vect, double radius)
{
	return (ft_lenght(vect) - radius);
}

void	raytracing(t_image *img)
{
	// t_camera	*cam = set_camera(set_point(0, 0, 0), set_point(0, 0, 1), 90);
	t_sphere	*sph = new_sphere(set_point(150, 150, 0), 10, 0xFF0000);
	t_point		vect;

	int	x = -1;
	int	y;
	while (++x < SCREEN_W)
	{
		y = -1;
		while (++y < SCREEN_H)
		{
			vect.x = x;
			vect.y = y;
			vect.z = 0;
			while (++vect.z < 100)
			{
				if (sd_sphere(soustract_vect(vect, *sph->pos), sph->diameter) < 0)
				{
					pixel_put(img, x, y, sph->color);
					break ;
				}
			}
		}
	}
}
