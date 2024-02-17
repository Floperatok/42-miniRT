/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nsalles <nsalles@student.42perpignan.fr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/16 23:42:59 by nsalles           #+#    #+#             */
/*   Updated: 2024/02/17 00:42:04 by nsalles          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

void	init_window(t_window *win)
{
	win->mlx = mlx_init();
	win->screen_height = 700;
	win->screen_width = 700;
	win->window = mlx_new_window(win->mlx, win->screen_width,\
		win->screen_height, "miniRT");
}

void	init_image(t_image *img, t_window win)
{
	img->image_width = win.screen_width;
	img->image_height = win.screen_height;
	img->image = mlx_new_image(win.mlx, img->image_width, img->image_height);
	img->addr = mlx_get_data_addr(img->image, &img->bits_per_pixel,\
		&img->line_length, &img->endian);
}

int	exit_handling(t_minirt *data)
{
	mlx_destroy_image(data->win.mlx, data->img.image);
	mlx_destroy_window(data->win.mlx, data->win.window);
	mlx_destroy_display(data->win.mlx);
	free(data->win.mlx);
	exit(EXIT_SUCCESS);
}