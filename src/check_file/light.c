/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   light.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: drenassi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/17 17:31:10 by drenassi          #+#    #+#             */
/*   Updated: 2024/02/18 12:44:23 by drenassi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

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

int	check_light(char **data)
{
	static int	l_count = 0;
	int			len;

	l_count++;
	if (l_count > 1)
		return (print_error("Error: Too much Lights.\n"));
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
