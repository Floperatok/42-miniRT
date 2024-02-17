/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sphere.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nsalles <nsalles@student.42perpignan.fr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/17 13:50:50 by nsalles           #+#    #+#             */
/*   Updated: 2024/02/17 16:12:11 by nsalles          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

/*
 *	Sphere struct destroyer.
*/
void	destroy_sphere(t_sphere *sphere)
{
	if (!sphere)
		return ;
	destroy_point(sphere->pos);
	free(sphere);
}

/*
 *	Create and return sphere struct.
*/
t_sphere	*get_sphere(t_point *pos, double diameter, int color)
{
	t_sphere	*sphere;

	sphere = malloc(sizeof(t_sphere));
	if (!sphere)
	{
		print_error("Fatal error: sphere struct initialization: ");
		print_error("Out of memory\n");
		return (NULL);
	}
	if (!pos)
	{
		free(sphere);
		destroy_point(pos);
		return (NULL);
	}
	sphere->pos = pos;
	sphere->diameter = diameter;
	sphere->color = color;
	return (sphere);
}
