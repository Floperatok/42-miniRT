/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   light.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: drenassi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/20 13:25:40 by drenassi          #+#    #+#             */
/*   Updated: 2024/02/20 13:42:18 by drenassi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

// void	apply_light_plane(float distance, t_plane *plane)
// {
	
// }

void	apply_light_sphere(float distance, float min_distance,
	t_data *data, t_plane *sphere)
{
	int		sum;
	t_color	color;
	t_point	light;

	color = int_to_rgb(data->light->color);
	sum = color.r + color.g + color.b;
	light.x = 3 * color.r * data->a_light->ratio / sum;
	light.y = 3 * color.g * data->a_light->ratio / sum;
	light.z = 3 * color.b * data->a_light->ratio / sum;
}

// void	apply_light(float distance, t_data *data, char *shape)
// {
// 	if (!ft_strcmp(shape, "plane"))
		
// }
