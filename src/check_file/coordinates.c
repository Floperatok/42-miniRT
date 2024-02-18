/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   coordinates.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: drenassi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/16 20:43:26 by drenassi          #+#    #+#             */
/*   Updated: 2024/02/18 12:16:56 by drenassi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

int	check_coordinates(char *coord)
{
	int		i;
	char	**vector;

	vector = ft_split(coord, ',');
	if (!vector)
		return (0);
	if (double_array_len(vector) != 3)
		return (free_double_array(vector), 0);
	i = 0;
	while (i < 3)
	{
		if (!check_double(vector[i]))
		return (free_double_array(vector), 0);
		i++;
	}
	return (free_double_array(vector), 1);
}

int	check_orientation_vector(char *coord)
{
	int		i;
	char	**vector;
	double	value;

	if (!check_coordinates(coord))
		return (0);
	vector = ft_split(coord, ',');
	i = 0;
	while (i < 3)
	{
		value = ft_atod(vector[i]);
		if (value < -1.0 || value > 1.0)
			return (free_double_array(vector), 0);
		i++;
	}
	return (free_double_array(vector), 1);
}
