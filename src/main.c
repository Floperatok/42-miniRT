/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: drenassi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/15 12:38:38 by nsalles           #+#    #+#             */
/*   Updated: 2024/02/22 12:08:55 by drenassi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

int	exit_handling(t_minirt *mem)
{
	if (!mem)
		exit(EXIT_FAILURE);
	if (mem->win)
		destroy_image(mem->img, mem->win->mlx);
	destroy_window(mem->win);
	destroy_data(mem->data);
	free(mem);
	exit(EXIT_SUCCESS);
}

t_minirt	*init_mem(void)
{
	t_minirt *mem;

	mem = malloc(sizeof(t_minirt));
	if (!mem)
	{
		print_error("Fatal error: mem initialization: Out of memory\n");
		exit_handling(mem);
	}
	mem->img = NULL;
	mem->win = NULL;
	mem->data = NULL;
	return (mem);
}

int main(int ac, char **av)
{
	t_minirt	*mem;

	if (ac != 2)
		return (print_error("Error: One argument needed.\n"), 1);
	if (!check_file(av[1]))
		return (1);
	mem = init_mem();
	mem->win = get_window();
	if (!mem->win)
		exit_handling(mem);
	mem->img = get_image(mem->win);
	if (!mem->img)
		exit_handling(mem);
	mem->data = set_data(av[1]);
	mlx_hook(mem->win->window, 17, 0L, &exit_handling, mem);
	mlx_hook(mem->win->window, 2, 1L << 0, &user_input, mem);
	apply_ambient_lightning(mem->data);
	rendering(mem);
	mlx_put_image_to_window(mem->win->mlx, mem->win->window, mem->img->image, 0, 0);
	mlx_loop(mem->win->mlx);
	return (0);
}
