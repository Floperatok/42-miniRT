/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nsalles <nsalles@student.42perpignan.fr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/15 12:38:38 by nsalles           #+#    #+#             */
/*   Updated: 2024/02/17 16:18:23 by nsalles          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

int	exit_handling(t_minirt *data)
{
	if (!data)
		exit(EXIT_FAILURE);
	if (data->win)
		destroy_image(data->img, data->win->mlx);
	destroy_window(data->win);
	free(data);
	exit(EXIT_SUCCESS);
}

t_minirt	*create_data(void)
{
	t_minirt *data;

	data = malloc(sizeof(t_minirt));
	if (!data)
	{
		print_error("Fatal error: data initialization: Out of memory\n");
		exit_handling(data);
	}
	data->img = NULL;
	data->win = NULL;
	data->shapes = NULL;
	return (data);
}

int main(int ac, char **av)
{
	t_minirt	*data;

	if (ac != 2)
		return (print_error("Error: One argument needed.\n"), 1);
	if (!check_file(av[1]))
		return (1);
	data = create_data();
	data->win = get_window();
	if (!data->win)
		exit_handling(data);
	data->img = get_image(data->win);
	if (!data->img)
		exit_handling(data);
	// get_values()
	mlx_hook(data->win->window, 17, 0L, &exit_handling, data);
	mlx_hook(data->win->window, 2, 1L << 0, &user_input, data);
	draw_image(NULL, data->img);
	mlx_put_image_to_window(data->win->mlx, data->win->window,\
		data->img->image, 0, 0);
	mlx_loop(data->win->mlx);
	return (0);
}
