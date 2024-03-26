/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lights.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nsalles <nsalles@student.42perpignan.fr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/04 16:00:42 by nsalles           #+#    #+#             */
/*   Updated: 2024/03/26 13:10:03 by nsalles          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

static t_color	apply_specular(t_color color, t_vec reflect, t_vec light_dir, 
	t_light	*light)
{
	double	specular;

	specular = dot(reflect, light_dir);
	if (specular > 0.5)
	{
		specular = pow(specular, 70) * light->brightness;
		color.r += light->color.r * specular;
		color.g += light->color.g * specular;
		color.b += light->color.b * specular;
	}
	if (specular > 0.5)
	{
		specular = pow(specular, 20) * light->brightness;
		color = add_color(color, specular * 0.3);
	}
	return (color);
}

static t_color	apply_ambient(t_color color, t_alight *alight)
{
	color.r *= alight->color.r * alight->ratio;
	color.g *= alight->color.g * alight->ratio;
	color.b *= alight->color.b * alight->ratio;
	return (color);
}

static t_color	apply_diffuse(t_color color, t_color base_color, t_light *light, double exposure)
{
	color.r += base_color.r * (light->color.r * light->brightness * exposure);
	color.g += base_color.g * (light->color.g * light->brightness * exposure);
	color.b += base_color.b * (light->color.b * light->brightness * exposure);
	return (color);
}

t_color	compute_lights(t_alight *alight, t_light **lights, t_hitinfo *hit, 
	t_objects *objs)
{
	t_color	color;
	t_vec	light_dir;
	double	light_dst;
	double	exposure;
	int		i;

	i = -1;
	color = hit->color;
	color = apply_ambient(color, alight);
	while (lights[++i])
	{
		light_dir = soustract_vect(lights[i]->pos, hit->pos);
		light_dst = ft_lenght(light_dir);
		light_dir = divide_vect(light_dir, light_dst);
		exposure = fmax(dot(hit->normal, light_dir), 0.0);
		if (is_in_shadow(hit->pos, light_dir, light_dst, objs) || !exposure)
			continue ;
		color = apply_diffuse(color, hit->color, lights[i], exposure);
		if (hit->specular)
			color = apply_specular(color, hit->reflect, light_dir, 
				lights[i]);
		protect_colors(&color);
	}
	return (color);
}
