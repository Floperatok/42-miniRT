/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lights.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nsalles <nsalles@student.42perpignan.fr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/04 16:00:42 by nsalles           #+#    #+#             */
/*   Updated: 2024/03/25 12:27:17 by nsalles          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#define SPECULAR_RATIO 0.1

#include "minirt.h"

// t_color	apply_light(t_light *light, t_hitinfo *hit, t_objects *objs)
// {
// 	t_vec		light_dir;
// 	double		light_dst;
// 	double		exposure;

// 	if (!light)
// 		return (hit->color);
// 	light_dir = soustract_vect(light->pos, hit->pos);
// 	light_dst = ft_lenght(light_dir);
// 	normalize_vect(&light_dir);
// 	exposure = dot(hit->normal, light_dir);
// 	if (exposure < 0)
// 		return (hit->color);
// if (is_in_shadow(hit->pos, light_dir, light_dst, objs))
// 		return (hit->color);
// 	exposure *= 5;
// 	exposure++;
// 	hit->color.r *= exposure;
// 	hit->color.g *= exposure;
// 	hit->color.b *= exposure;
// 	protect_colors(&hit->color);
// 	return (hit->color);
// }

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

static t_color	apply_ambient(t_color color, t_alight *alight)
{
	color.r *= alight->color.r * alight->ratio;
	color.g *= alight->color.g * alight->ratio;
	color.b *= alight->color.b * alight->ratio;
	return (color);
}

static t_color	apply_ambient_and_diffuse(t_color color, t_alight *alight,
	t_light *light, double exposure)
{
	color.r *= alight->color.r * alight->ratio + light->color.r * 
		light->brightness * exposure;
	color.g *= alight->color.g * alight->ratio + light->color.g * 
		light->brightness * exposure;
	color.b *= alight->color.b * alight->ratio + light->color.b * 
		light->brightness * exposure;
	return (color);	
}

t_color	compute_light(t_alight *alight, t_light *lights, t_hitinfo *hit, 
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
		color = apply_ambient(color, alight);
		return (color);
	}
	color = apply_ambient_and_diffuse(color, alight, light, exposure);
	if (hit->specular)
		color = specular_light(color, hit->reflect, light_dir, light->brightness);
	protect_colors(&color);
	return (color);
}
