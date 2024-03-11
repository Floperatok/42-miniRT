/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cylinder.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nsalles <nsalles@student.42perpignan.fr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/24 14:23:19 by nsalles           #+#    #+#             */
/*   Updated: 2024/03/11 17:33:20 by nsalles          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

void	destroy_cylinders(t_cylinder **cylinders)
{
	int	i;

	if (!cylinders)
		return ;
	i = -1;
	while (cylinders[++i])
		free(cylinders[i]);
	free(cylinders);
}

static t_cylinder	*new_cylinder(char **obj)
{
	t_cylinder	*cylinder;

	cylinder = malloc(sizeof(t_cylinder));
	cylinder->pos = get_point_from_string(obj[1], ',');
	cylinder->direction = get_point_from_string(obj[2], ',');
	cylinder->diameter = ft_atod(obj[3]);
	cylinder->height = ft_atod(obj[4]);
	cylinder->color = format_color(obj[5]);
	cylinder->reflect_ratio = ft_atod(obj[6]);
	return (cylinder);
}

/*
 *	Creates an array of t_cylinder structs with all the cylinders 
 *	found in the array objs. Returns the array.
*/
t_cylinder	**get_cylinders(char ***objs, int num_objects)
{
	int			i;
	int			j;
	int			counter;
	t_cylinder	**cylinders;

	i = -1;
	counter = 0;
	while (objs[++i])
		if (!ft_strcmp(objs[i][0], "cy"))
			counter++;
	cylinders = malloc(sizeof(t_cylinder *) * (counter + 1));
	i = -1;
	j = 0;
	while (++i < num_objects)
		if (!ft_strcmp(objs[i][0], "cy"))
			cylinders[j++] = new_cylinder(objs[i]);
	cylinders[j] = NULL;
	return (cylinders);
}
