/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   image.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nsalles <nsalles@student.42perpignan.fr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/16 23:42:59 by nsalles           #+#    #+#             */
/*   Updated: 2024/03/27 20:39:04 by nsalles          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

void	destroy_image(t_image *img, void *mlx)
{
	if (mlx && img->image)
		mlx_destroy_image(mlx, img->image);
}

int	get_image(t_image *img, t_window win)
{
	img->height = win.height;
	img->width = win.width;
	img->image = mlx_new_image(win.mlx, win.width, win.height);
	if (!img->image)
	{
		print_error("Fatal error: image initialization failed\n");
		return (destroy_image(img, win.mlx), 0);
	}
	img->addr = mlx_get_data_addr(img->image, &img->bits_per_pixel,
			&img->line_length, &img->endian);
	if (!img->addr)
	{
		print_error("Fatal error: image initialization failed\n");
		return (destroy_image(img, win.mlx), 0);
	}
	img->aspect_ratio = (double)img->width / (double)img->height;
	return (1);
}
