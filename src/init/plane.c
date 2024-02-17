/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   plane.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nsalles <nsalles@student.42perpignan.fr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/17 13:34:37 by nsalles           #+#    #+#             */
/*   Updated: 2024/02/17 19:09:44 by nsalles          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

/*
 *	Plane struct destroyer.
*/
void	destroy_plane(t_plane *plane)
{
	if (!plane)
		return ;
	destroy_point(plane->pos);
	destroy_point(plane->vector);
	free(plane);
}

/*
 *	Create, set the values and return plane struct.
*/
t_plane	*set_plane(t_point *pos, t_point *vector, int color)
{
	t_plane	*plane;

	plane = malloc(sizeof(plane));
	if (!plane)
	{
		print_error("Fatal error: plane struct initialization: ");
		print_error("Out of memory\n");
		return (NULL);
	}
	if (!pos || !vector)
	{
		free(plane);
		destroy_point(pos);
		destroy_point(vector);
		return (NULL);
	}
	plane->pos = pos;
	plane->vector = vector;
	plane->color = color;
	return (plane);
}
