/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sphere.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nsalles <nsalles@student.42perpignan.fr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/24 14:08:13 by nsalles           #+#    #+#             */
/*   Updated: 2024/03/11 17:33:39 by nsalles          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

void	destroy_spheres(t_sphere **spheres)
{
	int	i;

	i = -1;
	while (spheres[++i])
		free(spheres[i]);
	free(spheres);
}

static t_sphere	*new_sphere(char **obj)
{
	t_sphere	*sphere;

	sphere = malloc(sizeof(t_sphere));
	sphere->pos = get_point_from_string(obj[1], ',');
	sphere->radius = ft_atod(obj[2]) / 2;
	sphere->color = format_color(obj[3]);
	sphere->reflect_ratio = ft_atod(obj[4]);
	return (sphere);
}

/*
 *	Creates an array of t_sphere structs with all the spheres 
 *	found in the array objs. Returns the array.
*/
t_sphere	**get_spheres(char ***objs, int num_objects)
{
	int			i;
	int			j;
	int			counter;
	t_sphere	**spheres;

	i = -1;
	counter = 0;
	while (objs[++i])
		if (!ft_strcmp(objs[i][0], "sp"))
			counter++;
	spheres = malloc(sizeof(t_sphere *) * (counter + 1));
	i = -1;
	j = 0;
	while (++i < num_objects)
		if (!ft_strcmp(objs[i][0], "sp"))
			spheres[j++] = new_sphere(objs[i]);
	spheres[j] = NULL;
	return (spheres);
}
