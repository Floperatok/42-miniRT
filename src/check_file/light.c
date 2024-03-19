/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   light.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: drenassi <@student.42perpignan.fr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/17 17:31:10 by drenassi          #+#    #+#             */
/*   Updated: 2024/03/16 09:43:22 by drenassi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

/*
 *	Returns 1 if the input string has a ratio format in range [0.0-1.0].
 *	Returns 0 if not.
*/
static int	check_ratio(char *ratio)
{
	double	value;

	if (!check_double(ratio))
	{
		print_error("Error: Light: Ratio must be in range ");
		print_error("[0.0,1.0]. Example: 0.6\n");
		return (0);
	}
	value = ft_atod(ratio);
	if (value < 0.0 || value > 1.0)
	{
		print_error("Error: Light: Ratio must be in range ");
		print_error("[0.0,1.0]. Example: 0.6\n");
		return (0);
	}
	return (1);
}

/*
 *	Returns 1 if the given line has the correct format for light, 0 if not.
*/
int	check_light(char **data)
{
	int			len;

	len = double_array_len(data);
	if (len != 4)
		return (print_error("Error: Light needs 4 arguments.\n"));
	if (!check_coordinates(data[1]))
		return (print_error("Error: Camera: Wrong coordinates.\n"));
	if (!check_ratio(data[2]))
		return (0);
	if (!check_rgb(data[3]))
	{
		print_error("Error: Ambient lighting: RGB colors ");
		print_error("must be in range [0-255]. Example: 255,255,255\n");
		return (0);
	}
	return (1);
}
