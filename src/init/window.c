/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   window.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nsalles <nsalles@student.42perpignan.fr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/17 15:18:56 by nsalles           #+#    #+#             */
/*   Updated: 2024/02/24 12:24:59 by nsalles          ###   ########.fr       */
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

int	get_window(t_window *win)
{
	win->height = 800;
	win->width = 1200;
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
