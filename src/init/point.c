/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   point.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nsalles <nsalles@student.42perpignan.fr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/24 13:55:22 by nsalles           #+#    #+#             */
/*   Updated: 2024/02/24 14:01:58 by nsalles          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

t_point	get_point(double x, double y, double z)
{
	t_point	point;

	point.x = x;
	point.y = y;
	point.z = z;
	return (point);
}

t_point	get_point_from_string(char *string, char delimiter)
{
	char	**coords;
	double	x;
	double	y;
	double	z;

	coords = ft_split(string, delimiter);
	x = ft_atod(coords[0]);
	y = ft_atod(coords[1]);
	z = ft_atod(coords[2]);
	free_double_array(coords);
	return (get_point(x, y, z));
}
