/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lights.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nsalles <nsalles@student.42perpignan.fr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/04 16:00:42 by nsalles           #+#    #+#             */
/*   Updated: 2024/03/25 11:32:22 by nsalles          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

t_color	specular_light(t_color color, t_vec reflect, t_vec light_dir, 
	double brightness)
{
	double	specular;

	specular = dot(reflect, light_dir);
	if (specular > 0.5)
	{
		specular = pow(specular, 70) * brightness;
		color = add_color(color, specular);
	}
	return (color);
}

t_color	compute_lights(t_alight *alight, t_light *light, t_hitinfo *hit, 
	t_objects *objs)
{
	t_color	color;
	t_vec	light_dir;
	double	light_dst;
	double	exposure;

	color = hit->color;
	light_dir = soustract_vect(light->pos, hit->pos);
	light_dst = ft_lenght(light_dir);
	light_dir = divide_vect(light_dir, light_dst);
	exposure = fmax(dot(hit->normal, light_dir), 0.0);
	if (is_in_shadow(hit->pos, light_dir, light_dst, objs) || exposure == 0)
	{
		color = multiplies_color(color, alight->color.r * alight->ratio);
		return (color);
	}
	color = multiplies_color(color, alight->color.r * alight->ratio + 
		light->color.r * light->brightness * exposure);
	if (hit->specular)
		color = specular_light(color, hit->reflect, light_dir, light->brightness);
	protect_colors(&color);
	return (color);
}
