/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   plane.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nsalles <nsalles@student.42perpignan.fr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/24 14:45:22 by nsalles           #+#    #+#             */
/*   Updated: 2024/02/24 14:57:38 by nsalles          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

void	destroy_planes(t_plane *planes)
{
	if (planes)
		free(planes);
}

int	get_planes(char ***objs, t_plane **planes)
{
	int			i;
	int			j;
	int			counter;

	i = -1;
	counter = 0;
	while (objs[++i])
		if (!ft_strcmp(objs[i][0], "pl"))
			counter++;
	*planes = malloc(sizeof(t_plane) * counter);
	i = -1;
	j = 0;
	while (++i < counter)
	{
		if (!ft_strcmp(objs[i][0], "pl"))
		{
			planes[j]->pos = get_point_from_string(objs[i][1], ',');
			planes[j]->normal = get_point_from_string(objs[i][2], ',');
			planes[j]->color = format_color(objs[i][3]);
			j++;	
		}		
	}
	return (counter);
}