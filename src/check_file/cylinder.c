/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cylinder.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: drenassi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/17 18:13:12 by drenassi          #+#    #+#             */
/*   Updated: 2024/02/17 18:23:47 by drenassi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

int	check_cylinder(char **data)
{
	if (double_array_len(data) != 6)
		return (print_error("Error: Cylinder needs 5 arguments.\n"));
	if (!check_coordinates(data[1]))
		return (print_error("Error: Cylinder: Wrong coordinates.\n"));
	if (!check_orientation_vector(data[2]))
		return (print_error("Error: Cylinder: Wrong orientation vector. It "),
			print_error("must be in range [-1.0,1.0] for each axis.\n"));
	if (!check_float(data[3]) || ft_atof(data[3]) < 0.0)
		return (print_error("Error: Cylinder: Invalid diameter.\n"));
	if (!check_float(data[4]) || ft_atof(data[4]) < 0.0)
		return (print_error("Error: Cylinder: Invalid height.\n"));
	if (!check_rgb(data[5]))
	{
		print_error("Error: Cylinder: RGB colors ");
		print_error("must be in range [0-255]. Example: 255,255,255\n");
		return (0);
	}
	return (1);
}
