/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cylinder.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nsalles <nsalles@student.42perpignan.fr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/17 13:54:10 by nsalles           #+#    #+#             */
/*   Updated: 2024/02/18 02:09:45 by nsalles          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

/*
 *	Cylinder struct destroyer.
*/
void	destroy_cylinder(t_cylinder *cylinder)
{
	if (!cylinder)
		return ;
	destroy_point(cylinder->pos);
	destroy_point(cylinder->vector);
	free(cylinder);
}

/*
 *	Create, set the values and return cylinder struct.
*/
t_cylinder	*set_cylinder(t_point *pos, t_point *vector, double diameter,\
	double height, int color)
{
	t_cylinder	*cylinder;

	cylinder = malloc(sizeof(t_cylinder));
	if (!cylinder)
	{
		print_error("Fatal error: cylinder struct initialization: ");
		print_error("Out of memory\n");
		return (NULL);
	}
	if (!pos || !vector)
	{
		free(cylinder);
		destroy_point(pos);
		destroy_point(vector);
		return (NULL);
	}
	cylinder->pos = pos;
	cylinder->vector = vector;
	cylinder->diameter = diameter;
	cylinder->height = height;
	cylinder->color = color;
	return (cylinder);
}
