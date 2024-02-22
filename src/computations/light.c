/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   light.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: drenassi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/20 13:25:40 by drenassi          #+#    #+#             */
/*   Updated: 2024/02/22 11:51:10 by drenassi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

/*
*	Returns the base color of an object.
*/
t_color	get_obj_color(t_obj *obj)
{
	if (obj->pl)
		return (int_to_rgb(obj->pl->color));
	else if (obj->sp)
		return (int_to_rgb(obj->sp->color));
	else if (obj->cy)
		return (int_to_rgb(obj->cy->color));
	else
		return ((t_color){0, 0, 0, 0});
}

/*
*	Returns the light intensity.
*/
t_point	light_intensity(t_data *data)
{
	t_point			light_color;
	t_point			max_sum;

	light_color.x = int_to_rgb(data->light->color).r;
	light_color.y = int_to_rgb(data->light->color).g;
	light_color.z = int_to_rgb(data->light->color).b;
	max_sum = multiply_vect(light_color, \
		data->light->brightness / int_to_rgb(data->light->color).sum);
	return ((t_point){1 / max_sum.x, 1 / max_sum.y, 1 / max_sum.z});
}

/*
*	Returns the color resulting from a colored light applied
*	on a colored pixel.
*/
t_color	apply_light(t_data *data, t_closest_obj closest)
{
	t_color		obj_color;
	t_color		color;
	t_point		intensity;

	obj_color = get_obj_color(closest.obj);
	intensity = light_intensity(data);
	color.r = obj_color.r * intensity.x;
	color.g = obj_color.g * intensity.y;
	color.b = obj_color.b * intensity.z;
	color.sum = color.r + color.g + color.b;
	protect_colors(&color);
	return (color);
}
