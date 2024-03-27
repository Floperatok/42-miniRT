/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   light.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nsalles <nsalles@student.42perpignan.fr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/24 14:04:12 by nsalles           #+#    #+#             */
/*   Updated: 2024/03/27 20:39:30 by nsalles          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

void	destroy_lights(t_light **lights)
{
	int	i;

	i = -1;
	while (lights[++i])
		free(lights[i]);
	free(lights);
}

static t_light	*new_light(char **obj)
{
	t_light	*light;

	light = malloc(sizeof(t_light));
	light->pos = get_vec_from_string(obj[1], ',');
	light->brightness = ft_atod(obj[2]);
	light->color = format_color(obj[3]);
	return (light);
}

/*
 *	Creates an array of t_light structs with all the lights 
 *	found in the array objs. Returns the array.
*/
t_light	**get_lights(char ***objs, int num_objects)
{
	int		i;
	int		j;
	int		counter;
	t_light	**lights;

	i = -1;
	counter = 0;
	while (objs[++i])
		if (!ft_strcmp(objs[i][0], "L"))
			counter++;
	lights = malloc(sizeof(t_light *) * (counter + 1));
	i = -1;
	j = 0;
	while (++i < num_objects)
		if (!ft_strcmp(objs[i][0], "L"))
			lights[j++] = new_light(objs[i]);
	lights[j] = NULL;
	return (lights);
}
