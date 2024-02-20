/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ambient_lightning.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: drenassi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/19 16:07:33 by drenassi          #+#    #+#             */
/*   Updated: 2024/02/20 13:24:49 by drenassi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

static void	apply_planes_alight(t_point light, t_data *data)
{
	t_color	plane_color;
	t_plane	*planes;

	planes = data->planes;
	while (planes)
	{
		plane_color = int_to_rgb(planes->color);
		plane_color.r *= light.x;
		plane_color.g *= light.y;
		plane_color.b *= light.z;
		protect_colors(&plane_color);
		planes->color = rgb_to_int(plane_color.r, \
			plane_color.g, plane_color.b);
		planes = planes->next;
	}
}

static void	apply_spheres_alight(t_point light, t_data *data)
{
	t_color		sphere_color;
	t_sphere	*spheres;

	spheres = data->spheres;
	while (spheres)
	{
		sphere_color = int_to_rgb(spheres->color);
		sphere_color.r *= light.x;
		sphere_color.g *= light.y;
		sphere_color.b *= light.z;
		protect_colors(&sphere_color);
		spheres->color = rgb_to_int(sphere_color.r, \
			sphere_color.g, sphere_color.b);
		spheres = spheres->next;
	}
}

static void	apply_cylinders_alight(t_point light, t_data *data)
{
	t_color		cylinder_color;
	t_cylinder	*cylinders;

	cylinders = data->cylinders;
	while (cylinders)
	{
		cylinder_color = int_to_rgb(cylinders->color);
		cylinder_color.r *= light.x;
		cylinder_color.g *= light.y;
		cylinder_color.b *= light.z;
		protect_colors(&cylinder_color);
		cylinders->color = rgb_to_int(cylinder_color.r, \
			cylinder_color.g, cylinder_color.b);
		cylinders = cylinders->next;
	}
}

void	apply_ambient_lightning(t_data *data)
{
	int		sum;
	t_color	color;
	t_point	light;

	if (!data->a_light)
		return ;
	color = int_to_rgb(data->a_light->color);
	sum = color.r + color.g + color.b;
	light.x = 3 * color.r * data->a_light->ratio / sum;
	light.y = 3 * color.g * data->a_light->ratio / sum;
	light.z = 3 * color.b * data->a_light->ratio / sum;
	if (data->planes)
		apply_planes_alight(light, data);
	if (data->spheres)
		apply_spheres_alight(light, data);
	if (data->cylinders)
		apply_cylinders_alight(light, data);
}
