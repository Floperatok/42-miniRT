/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   point.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nsalles <nsalles@student.42perpignan.fr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/24 13:55:22 by nsalles           #+#    #+#             */
/*   Updated: 2024/03/19 16:35:02 by nsalles          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

t_vec	get_vec(double x, double y, double z)
{
	t_vec	point;

	point.x = x;
	point.y = y;
	point.z = z;
	return (point);
}

t_vec	get_vec_from_string(char *string, char delimiter)
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
	return (get_vec(x, y, z));
}
