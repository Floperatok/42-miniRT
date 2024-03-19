/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cone.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: drenassi <@student.42perpignan.fr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/17 14:41:48 by drenassi          #+#    #+#             */
/*   Updated: 2024/03/17 16:59:18 by drenassi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

/*
 *	Second part of the check_cone function.
*/
static int	check_cone2(char **data)
{
	if (data[6] && (!check_double(data[6]) \
		|| ft_atod(data[6]) < 0.0 || ft_atod(data[6]) > 1.0))
	{
		print_error("Error: Cylinder: Reflect ratio must be in range ");
		print_error("[0.0,1.0]. Example: 0.6\n");
		return (0);
	}
	return (1);
}

/*
 *	Returns 1 if the given line has the correct format for cone descriptor,
 *	0 if not.
*/
int	check_cone(char **data)
{
	int	len;

	len = double_array_len(data);
	if (len < 6 || len > 7)
		return (print_error("Error: Cone needs 5 or 6 arguments.\n"));
	if (!check_coordinates(data[1]))
		return (print_error("Error: Cone: Wrong coordinates.\n"));
	if (!check_orientation_vector(data[2]))
		return (print_error("Error: Cone: Wrong orientation vector. It "),
			print_error("must be in range [-1.0,1.0] for each axis.\n"));
	if (!check_double(data[3]) || ft_atod(data[3]) < 0.0)
		return (print_error("Error: Cone: Invalid diameter.\n"));
	if (!check_double(data[4]) || ft_atod(data[4]) < 0.0)
		return (print_error("Error: Cone: Invalid height.\n"));
	if (!check_rgb(data[5]))
	{
		print_error("Error: Cone: RGB colors ");
		print_error("must be in range [0-255]. Example: 255,255,255\n");
		return (0);
	}
	if (!check_cone2(data))
		return (0);
	return (1);
}
