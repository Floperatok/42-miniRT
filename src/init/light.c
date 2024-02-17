/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   light.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nsalles <nsalles@student.42perpignan.fr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/17 13:47:09 by nsalles           #+#    #+#             */
/*   Updated: 2024/02/17 16:09:02 by nsalles          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

/*
 *	Light struct destroyer.
*/
void	destroy_light(t_light *light)
{
	if (!light)
		return ;
	destroy_point(light->pos);
	free(light);
}

/*
 *	Create and return light struct.
*/
t_light	*get_light(t_point *pos, double brightness, int color)
{
	t_light	*light;

	light = malloc(sizeof(light));
	if (!light)
	{
		print_error("Fatal error: light struct initialization: ");
		print_error("Out of memory\n");
		return (NULL);
	}
	if (!pos)
	{
		free(light);
		destroy_point(pos);
		return (NULL);
	}
	light->pos = pos;
	light->brightness = brightness;
	light->color = color;
	return (light);
}
