/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   plane.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nsalles <nsalles@student.42perpignan.fr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/17 13:34:37 by nsalles           #+#    #+#             */
/*   Updated: 2024/02/17 14:19:43 by nsalles          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

/*
 *	Create and return plane struct.
*/
t_plane	*get_plane(t_point *pos, t_point *vector, int color)
{
	t_plane	*plane;

	plane = malloc(sizeof(plane));
	if (!plane)
		return (NULL);
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