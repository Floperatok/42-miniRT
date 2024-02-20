/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   window.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nsalles <nsalles@student.42perpignan.fr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/17 15:18:56 by nsalles           #+#    #+#             */
/*   Updated: 2024/02/20 23:33:03 by nsalles          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

void	destroy_window(t_window *win)
{
	if (!win)
		return ;
	if (win->window && win->mlx)
		mlx_destroy_window(win->mlx, win->window);
	if (win->mlx)
		mlx_destroy_display(win->mlx);
	free(win->mlx);
	free(win);
}

t_window	*get_window(void)
{
	t_window	*win;


	win = ft_calloc(1, sizeof(t_window));
	win->height = 800;
	win->width = 1200;
	if (!win)
	{
		print_error("Fatal error: window initialization: Out of memory\n");
		return (NULL);
	}
	win->window = NULL;
	win->mlx = mlx_init();
	if (!win->mlx)
	{
		print_error("Fatal error: mlx initialization failed\n");
		return (destroy_window(win), NULL);
	}
	win->window = mlx_new_window(win->mlx, win->width, win->height, "miniRT");
	if (!win->window)
	{
		print_error("Fatal error: window initialization failed\n");
		return (destroy_window(win), NULL);
	}
	return (win);
}
