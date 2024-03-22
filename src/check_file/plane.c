/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   plane.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nsalles <nsalles@student.42perpignan.fr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/17 18:09:21 by drenassi          #+#    #+#             */
/*   Updated: 2024/03/22 11:55:23 by nsalles          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

/*
 *	Returns 1 if the given line has the correct format for plane descriptor,
 *	0 if not.
*/
int	check_plane(char **data, int size)
{
	if (size < 4)
		return (print_error("Error: Plane needs at least 3 arguments.\n"));
	if (size > 6)
		return (print_error("Error: Plane can at most have 5 arguments.\n"));
	if (!check_coordinates(data[1]))
		return (print_error("Error: Plane: Wrong coordinates.\n"));
	if (!check_orientation_vector(data[2]))
		return (print_error("Error: Plane: Wrong orientation vector. It "),
			print_error("must be in range [-1.0,1.0] for each axis.\n"));
	if (!check_rgb(data[3]))
	{
		print_error("Error: Plane: RGB colors must be in range");
		return (print_error(" [0-255]. Example: 255,255,255\n"));
	}
	if (size >= 5 && (!check_double(data[4]) || !check_ratio(data[4])))
		return (print_error("Error: Plane: Invalid reflect ratio\n"));
	if (size == 6 && (!check_double(data[5]) || ft_atod(data[5]) < 0.0))
		return (print_error("Error: Plane: Invalid specular value\n"));
	return (1);
}
