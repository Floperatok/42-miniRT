/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sphere.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: drenassi <@student.42perpignan.fr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/17 18:01:28 by drenassi          #+#    #+#             */
/*   Updated: 2024/03/17 15:00:04 by drenassi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

/*
 *	Second part of the check_sphere function.
*/
static int	check_sphere2(char **data)
{
	if (data[4] && (!check_double(data[4]) || ft_atod(data[4]) < 0.0
			|| ft_atod(data[4]) > 1.0))
	{
		print_error("Error: Sphere: Reflect ratio must be in range ");
		print_error("[0.0,1.0]. Example: 0.6\n");
		return (0);
	}
	return (1);
}

/*
 *	Returns 1 if the given line has the correct format for sphere descriptor,
 *	0 if not.
*/
int	check_sphere(char **data)
{
	int	len;

	len = double_array_len(data);
	if (len < 4 || len > 5)
		return (print_error("Error: Sphere needs 3 or 4 arguments.\n"));
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
	if (!check_sphere2(data))
		return (0);
	return (1);
}
