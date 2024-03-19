/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cylinder.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nsalles <nsalles@student.42perpignan.fr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/24 14:23:19 by nsalles           #+#    #+#             */
/*   Updated: 2024/03/19 16:35:02 by nsalles          ###   ########.fr       */
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
	t_cylinder	*cy;

	cy = malloc(sizeof(t_cylinder));
	cy->pos = get_vec_from_string(obj[1], ',');
	cy->dir = get_vec_from_string(obj[2], ',');
	cy->radius = ft_atod(obj[3]) * 0.5;
	cy->height = ft_atod(obj[4]);
	cy->color = format_color(obj[5]);
	cy->reflect_ratio = ft_atod(obj[6]);
	cy->a = cy->pos;
	cy->b = add_vect(cy->pos, multiply_vect(cy->dir, cy->height));
	cy->ba = soustract_vect(cy->b, cy->a);
	cy->baba = dot(cy->ba, cy->ba);
	return (cy);
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
