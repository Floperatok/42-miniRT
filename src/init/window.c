/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   window.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: drenassi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/17 15:18:56 by nsalles           #+#    #+#             */
/*   Updated: 2024/02/18 13:09:25 by drenassi         ###   ########.fr       */
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
	win->window = mlx_new_window(win->mlx, SCREEN_W, SCREEN_H, "miniRT");
	if (!win->window)
	{
		print_error("Fatal error: window initialization failed\n");
		return (destroy_window(win), NULL);
	}
	return (win);
}
