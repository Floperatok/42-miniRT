/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cylinder.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nsalles <nsalles@student.42perpignan.fr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/17 13:54:10 by nsalles           #+#    #+#             */
/*   Updated: 2024/02/17 14:16:32 by nsalles          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

/*
 *	Create and return cylinder struct.
*/
t_cylinder	*get_cylinder(t_point *pos, t_point *vector, double diameter,\
	double height, int color)
{
	t_cylinder	*cylinder;

	cylinder = malloc(sizeof(t_cylinder));
	if (!cylinder)
		return (NULL);
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