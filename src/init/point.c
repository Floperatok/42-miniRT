/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   point.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: drenassi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/17 13:31:47 by nsalles           #+#    #+#             */
/*   Updated: 2024/02/18 12:54:49 by drenassi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

t_point	*str_to_point(char *str)
{
	char	**split;
	t_point	*point;

	split = ft_split(str, ',');
	point = set_point(ft_atod(split[0]), ft_atod(split[1]), ft_atod(split[2]));
	free_double_array(split);
	return (point);
}

/*
 *	Point struct destroyer.
*/
void	destroy_point(t_point *point)
{
	if (!point)
		return ;
	free(point);
}

/*
 *	Create, set the values and return point struct.
*/
t_point	*set_point(double x, double y, double z)
{
	t_point	*point;

	point = ft_calloc(1, sizeof(t_point));
	if (!point)
	{
		print_error("Fatal error: point struct initialization: ");
		print_error("Out of memory\n");
		return (NULL);
	}
	point->x = x;
	point->y = y;
	point->z = z;
	return (point);
}
