/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   light_source.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nsalles <nsalles@student.42perpignan.fr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/04 16:00:42 by nsalles           #+#    #+#             */
/*   Updated: 2024/03/05 16:22:31 by nsalles          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

int	apply_light(t_light *light, t_hitinfo *hit, t_objects *objs)
{
	t_point		light_dir;
	t_color		color;
	double		exposure;

	if (!light)
		return (hit->color);
	light_dir = soustract_vect(light->pos, hit->hit_point);
	normalize_vect(&light_dir);
	exposure = dot(hit->normal_dir, light_dir);
	if (exposure < 0)
		return (hit->color);
	if (is_in_shadow(hit->hit_point, light_dir, objs))
		return (hit->color);
	exposure *= 5;
	exposure++;
	color = int_to_rgb(hit->color);
	color.r *= exposure;
	color.g *= exposure;
	color.b *= exposure;
	protect_colors(&color);
	return (rgb_to_int(color.r, color.g, color.b));
}
