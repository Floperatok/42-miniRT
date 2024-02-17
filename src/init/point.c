/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   point.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nsalles <nsalles@student.42perpignan.fr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/17 13:31:47 by nsalles           #+#    #+#             */
/*   Updated: 2024/02/17 16:11:55 by nsalles          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

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
 *	Create and return point struct.
*/
t_point	*get_point(double x, double y, double z)
{
	t_point	*point;

	point = malloc(sizeof(t_point));
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
