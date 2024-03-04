/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   light_source.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nsalles <nsalles@student.42perpignan.fr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/04 16:00:42 by nsalles           #+#    #+#             */
/*   Updated: 2024/03/04 18:01:30 by nsalles          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

int	apply_light(t_light *light, t_hitinfo *hit)
{
	t_point	offset_pos;
	t_color	color;
	double	doted;

	if (!light)
		return (hit->color);
	offset_pos = soustract_vect(light->pos, hit->hit_point);
	normalize_vect(&offset_pos);
	doted = dot(hit->normal_dir, offset_pos);
	if (doted < 0)
		return (hit->color);
	doted *= 5;
	doted++;
	color = int_to_rgb(hit->color);
	color.r *= doted;
	color.g *= doted;
	color.b *= doted;
	protect_colors(&color);
	return (rgb_to_int(color.r, color.g, color.b));
}
