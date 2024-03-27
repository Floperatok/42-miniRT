/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   planes.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nsalles <nsalles@student.42perpignan.fr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/27 14:37:05 by nsalles           #+#    #+#             */
/*   Updated: 2024/03/27 20:35:53 by nsalles          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

/*
 *	Detects whether the ray encounters a plane. If it does, returns the
 *	distance of the plane. Else returns -1.
*/
static double	one_plane_intersection(t_ray ray, t_plane *plane)
{
	double	scalar;
	t_vec	offset_ray;

	scalar = dot(ray.dir, plane->normal);
	offset_ray = soustract_vect(plane->pos, ray.origin);
	return (dot(plane->normal, offset_ray) / scalar);
}

static void	pl_closest_hit(t_hitinfo *closest_hit, t_ray ray,
	t_plane *closest_pl)
{
	closest_hit->did_hit = 1;
	closest_hit->pos = add_vect(ray.origin,
			multiply_vect(ray.dir, closest_hit->dst));
	if (dot(ray.dir, closest_pl->normal) > 0)
		closest_hit->normal = normalize(
				multiply_vect(closest_pl->normal, -1));
	else
		closest_hit->normal = normalize(closest_pl->normal);
	closest_hit->color = closest_pl->color;
	closest_hit->reflect_ratio = closest_pl->reflect_ratio;
	closest_hit->specular = closest_pl->specular;
}

void	planes_intersection(t_ray ray, t_plane **planes,
	t_hitinfo *closest_hit)
{
	double	dst;
	t_plane	*closest_plane;
	int		i;

	closest_plane = NULL;
	i = -1;
	while (planes[++i])
	{
		dst = one_plane_intersection(ray, planes[i]);
		if (dst > 0.001 && dst < closest_hit->dst)
		{
			closest_plane = planes[i];
			closest_hit->dst = dst;
		}
	}
	if (!closest_plane)
		return ;
	pl_closest_hit(closest_hit, ray, closest_plane);
}
