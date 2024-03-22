/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cylinder.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nsalles <nsalles@student.42perpignan.fr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/17 18:13:12 by drenassi          #+#    #+#             */
/*   Updated: 2024/03/22 11:54:47 by nsalles          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

/*
 *	Returns 1 if the given line has the correct format for cylinder descriptor,
 *	0 if not.
*/
int	check_cylinder(char **data, int size)
{
	if (size < 6)
		return (print_error("Error: Cylinder needs at least 5 arguments.\n"));
	if (size > 8)
		return (print_error("Error: Cylinder can at most have 7 arguments.\n"));
	if (!check_coordinates(data[1]))
		return (print_error("Error: Cylinder: Wrong coordinates.\n"));
	if (!check_orientation_vector(data[2]))
		return (print_error("Error: Cylinder: Wrong orientation vector. It "),
			print_error("must be in range [-1.0,1.0] for each axis.\n"));
	if (!check_double(data[3]) || ft_atod(data[3]) < 0.0)
		return (print_error("Error: Cylinder: Invalid diameter.\n"));
	if (!check_double(data[4]) || ft_atod(data[4]) < 0.0)
		return (print_error("Error: Cylinder: Invalid height.\n"));
	if (!check_rgb(data[5]))
	{
		print_error("Error: Cylinder: RGB colors must be in range");
		return (print_error(" [0-255]. Example: 255,255,255\n"));
	}
	if (size >= 7 && (!check_double(data[6]) || !check_ratio(data[6])))
		return (print_error("Error: Cylinder: Invalid reflect ratio\n"));
	if (size == 8 && (!check_double(data[7]) || ft_atod(data[7]) < 0.0))
		return (print_error("Error: Cylinder: Invalid specular value\n"));
	return (1);
}
