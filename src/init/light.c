/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   light.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nsalles <nsalles@student.42perpignan.fr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/24 14:04:12 by nsalles           #+#    #+#             */
/*   Updated: 2024/03/19 16:35:02 by nsalles          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

void	destroy_light(t_light *light)
{
	if (light)
		free(light);
}

/*
 *	Creates and returns the light object if found.
*/
t_light	*get_light(char ***objs)
{
	int		i;
	t_light	*light;

	i = 0;
	while (objs[i] && ft_strcmp(objs[i][0], "L"))
		i++;
	if (!objs[i])
		return (NULL);
	light = malloc(sizeof(t_light));
	light->pos = get_vec_from_string(objs[i][1], ',');
	light->brightness = ft_atod(objs[i][2]);
	light->color = format_color(objs[i][3]);
	return (light);
}
