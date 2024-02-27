/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   plane.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nsalles <nsalles@student.42perpignan.fr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/24 14:45:22 by nsalles           #+#    #+#             */
/*   Updated: 2024/02/27 13:07:15 by nsalles          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

void	destroy_planes(t_plane **planes)
{
	int	i;

	if (!planes)
		return ;
	i = -1;
	while (planes[++i])
		free(planes[i]);
	free(planes);
}

static t_plane	*new_plane(char **obj)
{
	t_plane	*plane;

	plane = malloc(sizeof(t_plane));
	plane->pos = get_point_from_string(obj[1], ',');
	plane->normal = get_point_from_string(obj[2], ',');
	plane->color = format_color(obj[3]);
	return (plane);
}

/*
 *	Creates an array of t_plane structs with all the planes 
 *	found in the array objs. Returns the array.
*/
t_plane	**get_planes(char ***objs)
{
	int			i;
	int			j;
	int			counter;
	t_plane		**planes;

	i = -1;
	counter = 0;
	while (objs[++i])
		if (!ft_strcmp(objs[i][0], "pl"))
			counter++;
	planes = malloc(sizeof(t_plane *) * (counter + 1));
	i = -1;
	j = 0;
	while (++i < counter + 1)
		if (!ft_strcmp(objs[i][0], "pl"))
			planes[j++] = new_plane(objs[i]);
	planes[j] = NULL;
	return (planes);
}
