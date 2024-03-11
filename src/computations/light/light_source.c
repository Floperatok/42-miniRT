/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   light_source.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nsalles <nsalles@student.42perpignan.fr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/04 16:00:42 by nsalles           #+#    #+#             */
/*   Updated: 2024/03/11 14:48:14 by nsalles          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

t_color	apply_light(t_light *light, t_hitinfo *hit, t_objects *objs)
{
	t_point		light_dir;
	double		light_dst;
	double		exposure;

	if (!light)
		return (hit->color);
	light_dir = soustract_vect(light->pos, hit->hit_point);
	light_dst = ft_lenght(light_dir);
	normalize_vect(&light_dir);
	exposure = dot(hit->normal_dir, light_dir);
	if (exposure < 0)
		return (hit->color);
	if (is_in_shadow(hit->hit_point, light_dir, light_dst, objs))
		return (hit->color);
	exposure *= 5;
	exposure++;
	hit->color.r *= exposure;
	hit->color.g *= exposure;
	hit->color.b *= exposure;
	protect_colors(&hit->color);
	return (hit->color);
}
