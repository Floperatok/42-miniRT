/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sphere.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nsalles <nsalles@student.42perpignan.fr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/24 14:08:13 by nsalles           #+#    #+#             */
/*   Updated: 2024/02/25 15:03:07 by nsalles          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

void	destroy_spheres(t_sphere *spheres)
{
	if (spheres)
		free(spheres);
}

int	get_spheres(char ***objs, t_sphere **spheres)
{
	int			i;
	int			j;
	int			counter;

	i = -1;
	counter = 0;
	while (objs[++i])
		if (!ft_strcmp(objs[i][0], "sp"))
			counter++;
	*spheres = malloc(sizeof(t_sphere) * counter);
	i = -1;
	j = 0;
	while (++i < counter + 1)
	{
		if (!ft_strcmp(objs[i][0], "sp"))
		{
			spheres[j]->pos = get_point_from_string(objs[i][1], ',');
			spheres[j]->diameter = ft_atod(objs[i][2]);
			spheres[j]->color = format_color(objs[i][3]);
			j++;	
		}		
	}
	return (counter);
}
