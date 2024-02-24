/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cylinder.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nsalles <nsalles@student.42perpignan.fr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/24 14:23:19 by nsalles           #+#    #+#             */
/*   Updated: 2024/02/24 14:57:47 by nsalles          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

void	destroy_cylinders(t_cylinder *cylinders)
{
	if (cylinders)
		free(cylinders);
}

int	get_cylinders(char ***objs, t_cylinder **cylinders)
{
	int			i;
	int			j;
	int			counter;

	i = -1;
	counter = 0;
	while (objs[++i])
		if (!ft_strcmp(objs[i][0], "cy"))
			counter++;
	*cylinders = malloc(sizeof(t_cylinder) * counter);
	i = -1;
	j = 0;
	while (++i < counter)
	{
		if (!ft_strcmp(objs[i][0], "cy"))
		{
			cylinders[j]->pos = get_point_from_string(objs[i][1], ',');
			cylinders[j]->direction = get_point_from_string(objs[i][2], ',');
			cylinders[j]->diameter = ft_atod(objs[i][3]);
			cylinders[j]->height = ft_atod(objs[i][4]);
			cylinders[j]->color = format_color(objs[i][5]);
			j++;	
		}		
	}
	return (counter);
}
