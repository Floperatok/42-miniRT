/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ambiant_lightning.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: drenassi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/15 19:07:50 by drenassi          #+#    #+#             */
/*   Updated: 2024/02/18 11:20:56 by drenassi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

static int	check_ratio(char *ratio)
{
	float	value;

	if (!check_double(ratio))
	{
		print_error("Error: Ambiant lightning: Ratio must be in range ");
		print_error("[0.0,1.0]. Example: 0.2\n");
		return (0);
	}
	value = ft_atod(ratio);
	if (value < 0.0 || value > 1.0)
	{
		print_error("Error: Ambiant lightning: Ratio must be in range ");
		print_error("[0.0,1.0]. Example: 0.2\n");
		return (0);
	}
	return (1);
}

int check_ambiant_lightning(char **data)
{
	static int	a_count = 0;

	a_count++;
	if (a_count > 1)
		return (print_error("Error: Too much Ambient lightnings.\n"));
	if (double_array_len(data) != 3)
		return (print_error("Error: Ambient lightning needs 2 arguments.\n"));
	if (!check_ratio(data[1]))
		return (0);
	if (!check_rgb(data[2]))
	{
		print_error("Error: Ambient lighting: RGB colors ");
		print_error("must be in range [0-255]. Example: 255,255,255\n");
		return (0);
	}
	return (1);
}
