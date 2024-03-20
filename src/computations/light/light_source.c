/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   light_source.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nsalles <nsalles@student.42perpignan.fr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/04 16:00:42 by nsalles           #+#    #+#             */
/*   Updated: 2024/03/20 22:19:46 by nsalles          ###   ########.fr       */
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

t_color	apply_light(t_alight *alight, t_light *light, t_hitinfo *hit, 
	t_objects *objs)
{
	t_color	color;
	t_vec	light_dir;
	double	light_dst;
	double	exposure;
	double	tmp;
	(void)objs;

	color = hit->color;
	light_dir = soustract_vect(light->pos, hit->pos);
	light_dst = ft_lenght(light_dir);
	light_dir = divide_vect(light_dir, light_dst);
	exposure = fmax(dot(hit->normal, light_dir), 0.0);
	color = apply_ambient_lightning(alight, color);
	if (is_in_shadow(hit->pos, light_dir, light_dst, objs))
		return (color);
	tmp = exposure;
	exposure *= 5;
	exposure++;
	color.r *= exposure;
	color.g *= exposure;
	color.b *= exposure;
	if (tmp > 0.75)
	{
		color.r += pow(tmp, 100) * 0.5;
		color.g += pow(tmp, 100) * 0.5;
		color.b += pow(tmp, 100) * 0.5;
	}
	protect_colors(&color);
	return (color);
}
