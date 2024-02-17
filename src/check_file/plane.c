/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   plane.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: drenassi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/17 18:09:21 by drenassi          #+#    #+#             */
/*   Updated: 2024/02/17 18:16:45 by drenassi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

int	check_plane(char **data)
{
	if (double_array_len(data) != 4)
		return (print_error("Error: Plane needs 3 arguments.\n"));
	if (!check_coordinates(data[1]))
		return (print_error("Error: Plane: Wrong coordinates.\n"));
	if (!check_orientation_vector(data[2]))
		return (print_error("Error: Plane: Wrong orientation vector. It "),
			print_error("must be in range [-1.0,1.0] for each axis.\n"));
	if (!check_rgb(data[3]))
	{
		print_error("Error: Plane: RGB colors ");
		print_error("must be in range [0-255]. Example: 255,255,255\n");
		return (0);
	}
	return (1);
}
