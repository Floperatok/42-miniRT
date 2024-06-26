/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   window.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nsalles <nsalles@student.42perpignan.fr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/17 15:18:56 by nsalles           #+#    #+#             */
/*   Updated: 2024/03/22 12:40:58 by nsalles          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

void	destroy_window(t_window *win)
{
	if (win->window && win->mlx)
		mlx_destroy_window(win->mlx, win->window);
	if (win->mlx)
		mlx_destroy_display(win->mlx);
	free(win->mlx);
}

int	init_window(t_window *win, t_camera *camera)
{
	win->width = camera->screen_w;
	win->height = camera->screen_h;
	win->window = NULL;
	win->mlx = mlx_init();
	if (!win->mlx)
	{
		print_error("Fatal error: mlx initialization failed\n");
		return (destroy_window(win), 0);
	}
	win->window = mlx_new_window(win->mlx, win->width, win->height, "miniRT");
	if (!win->window)
	{
		print_error("Fatal error: window initialization failed\n");
		return (destroy_window(win), 0);
	}
	return (1);
}
