/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nsalles <nsalles@student.42perpignan.fr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/15 12:38:38 by nsalles           #+#    #+#             */
/*   Updated: 2024/03/22 12:46:44 by nsalles          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

int	exit_handling(t_minirt *data)
{
	destroy_image(&data->img, data->win.mlx);
	destroy_window(&data->win);
	destroy_objects(&data->objs);
	exit(EXIT_SUCCESS);
}

int main(int ac, char **av)
{
	t_minirt	data;
	int			hardware;

	if (!check_input(ac, av, &hardware))
		return (1);
	if (!check_file(av[1]))
		return (1);
	if (!get_objects(&data.objs, av[1]))
		return (1);
	if (!init_window(&data.win, data.objs.camera))
		return (destroy_objects(&data.objs), 1);
	if (!get_image(&data.img, data.win))
		return (destroy_objects(&data.objs), destroy_window(&data.win), 1);
	mlx_hook(data.win.window, 17, 0L, &exit_handling, &data);
	mlx_hook(data.win.window, 2, 1L << 0, &user_input, &data);
	if (hardware == 0)
		render_one_thread(&data);
	if (hardware == 1)
		render_multiple_threads(&data, 6);
	mlx_loop(data.win.mlx);
	return (0);
}
