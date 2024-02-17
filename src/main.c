/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nsalles <nsalles@student.42perpignan.fr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/15 12:38:38 by nsalles           #+#    #+#             */
/*   Updated: 2024/02/17 00:56:08 by nsalles          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

int main(int ac, char **av)
{
	t_minirt	data;

	if (ac != 2)
		return (print_error("Error: One argument needed.\n"), 1);
	if (!check_file(av[1]))
		return (1);
	init_window(&data.win);
	init_image(&data.img, data.win);
	// get_values()
	mlx_hook(data.win.window, 17, 0L, &exit_handling, &data);
	mlx_hook(data.win.window, 2, 1L << 0, &user_input, &data);
	draw_image(&data.img, NULL);
	mlx_put_image_to_window(data.win.mlx, data.win.window, data.img.image, 0, 0);
	mlx_loop(data.win.mlx);
	return (0);
}
