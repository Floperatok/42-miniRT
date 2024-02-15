/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ambiant_lightning.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: drenassi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/15 19:07:50 by drenassi          #+#    #+#             */
/*   Updated: 2024/02/15 20:44:10 by drenassi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

int	check_ratio(char *ratio)
{
	int	i;
	int	error;

	error = 0;
	i = 0;
	if (ratio[i] < '0' || ratio[i++] > '1')
		error = 1;
	if (ratio[i++] != '.')
		error = 1;
	if (ratio[i] < '0' || ratio[i++] > '9')
		error = 1;
	if (ratio[i])
		error = 1;
	if (error)
		return (print_error("Error: Wrong syntax for Ambient lightning.\n"),
			print_error("Ratio must be in range [0.0,1.0]. Example: 0.2\n"));
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
		print_error("Error: Wrong syntax for Ambient lighting.\nRGB colors ");
		print_error("must be in range [0-255].\nExample: 255,255,255\n");
		return (0);
	}
	return (1);
}
