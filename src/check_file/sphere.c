/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sphere.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nsalles <nsalles@student.42perpignan.fr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/17 18:01:28 by drenassi          #+#    #+#             */
/*   Updated: 2024/03/22 11:57:35 by nsalles          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

/*
 *	Returns 1 if the given line has the correct format for sphere descriptor,
 *	0 if not.
*/
int	check_sphere(char **data, int size)
{
	if (size < 4)
		return (print_error("Error: Sphere needs at least 3 arguments.\n"));
	if (size > 6)
		return (print_error("Error: Sphere can at most have 5 arguments.\n"));
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
	if (size >= 5 && (!check_double(data[4]) || !check_ratio(data[4])))
		return (print_error("Error: Sphere: Invalid reflect ratio\n"));
	if (size == 6 && (!check_double(data[5]) || ft_atod(data[5]) < 0.0))
		return (print_error("Error: Sphere: Invalid specular value\n"));
	return (1);
}
