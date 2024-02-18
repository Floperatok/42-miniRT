/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   image.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: drenassi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/16 23:42:59 by nsalles           #+#    #+#             */
/*   Updated: 2024/02/18 13:10:00 by drenassi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

void	destroy_image(t_image *img, void *mlx)
{
	if (!img)
		return ;
	if (!mlx)
	{
		free(img);
		return ;
	}
	if (img->image)
		mlx_destroy_image(mlx, img->image);
	free(img);
}

t_image	*get_image(t_window *win)
{
	t_image	*img;

	img = ft_calloc(1, sizeof(t_image));
	if (!img)
	{
		print_error("Fatal error: image initialization: Out of memory\n");
		return (NULL);
	}
	img->image = mlx_new_image(win->mlx, SCREEN_W, SCREEN_H);
	if (!img->image)
	{
		print_error("Fatal error: image initialization failed\n");
		return (destroy_image(img, win->mlx), NULL);
	}
	img->addr = mlx_get_data_addr(img->image, &img->bits_per_pixel,\
		&img->line_length, &img->endian);
	if (!img->addr)
	{
		print_error("Fatal error: image initialization failed\n");
		return (destroy_image(img, win->mlx), NULL);
	}
	return (img);
}
