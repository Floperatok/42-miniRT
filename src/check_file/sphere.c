/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sphere.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: drenassi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/17 18:01:28 by drenassi          #+#    #+#             */
/*   Updated: 2024/02/18 11:23:32 by drenassi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

int	check_sphere(char **data)
{
	if (double_array_len(data) != 4)
		return (print_error("Error: Sphere needs 3 arguments.\n"));
	if (!check_coordinates(data[1]))
		return (print_error("Error: Sphere: Wrong coordinates.\n"));
	if (!check_double(data[2]) || ft_atod(data[2]) < 0.0)
		return (print_error("Error: Sphere: Invalid diameter.\n"));
	if (!check_rgb(data[3]))
	{
		print_error("Error: Sphere: RGB colors ");
		print_error("must be in range [0-255]. Example: 255,255,255\n");
		return (0);
	}
	return (1);
}
