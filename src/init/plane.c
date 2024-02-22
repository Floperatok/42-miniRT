/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   plane.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: drenassi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/17 13:34:37 by nsalles           #+#    #+#             */
/*   Updated: 2024/02/21 17:20:30 by drenassi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

/*
 *	Plane struct destroyer.
*/
static void	destroy_one_plane(t_plane *plane)
{
	if (!plane)
		return ;
	destroy_point(plane->pos);
	destroy_point(plane->normal);
	free(plane);
}

void	destroy_plane(t_plane **plane)
{
	t_plane	*tmp;

	if (!plane)
		return ;
	tmp = *plane;
	while (*plane)
	{
		tmp = (*plane)->next;
		destroy_one_plane(*plane);
		*plane = tmp;
	}
	plane = NULL;
}

/*
 *	Create, set the values and return plane struct.
*/
static t_plane	*new_plane(t_point *pos, t_point *vector, int color)
{
	t_plane	*plane;

	plane = ft_calloc(1, sizeof(t_plane));
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
	plane->normal = vector;
	plane->color = color;
	plane->next = NULL;
	return (plane);
}

static t_plane	*get_last_plane(t_plane *plane)
{
	if (!plane)
		return (NULL);
	while (plane->next)
		plane = plane->next;
	return (plane);
}

void	set_plane(t_plane **plane, t_point *pos, t_point *vector, int clr)
{
	t_plane	*new;
	t_plane	*tmp;

	new = new_plane(pos, vector, clr);
	if (!*plane)
	{
		*plane = new;
		return ;
	}
	tmp = get_last_plane(*plane);
	tmp->next = new;
}
