/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   planes.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nsalles <nsalles@student.42perpignan.fr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/27 14:37:05 by nsalles           #+#    #+#             */
/*   Updated: 2024/03/04 15:40:06 by nsalles          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

/*
 *	Detects whether the ray encounters a plane. If it does, returns the
 *	distance of the plane. Else returns -1.
*/
static double	one_plane_collision(t_ray ray, t_plane *plane)
{
	double	scalar;
	t_point	offset_ray;

	scalar = dot(ray.dir, plane->normal);
	offset_ray = soustract_vect(plane->pos, ray.origin);
	return (dot(plane->normal, offset_ray) / scalar);
}

/*
 *
*/
void	planes_collision(t_ray ray, t_plane **planes, t_hitinfo *closest_hit)
{
	double	dst;
	t_plane	*closest_plane;
	int		i;

	closest_plane = NULL;
	i = -1;
	while (planes[++i])
	{
		dst = one_plane_collision(ray, planes[i]);
		if (dst > 0.001 && dst < closest_hit->dst)
		{
			closest_plane = planes[i];
			closest_hit->dst = dst;
		}
	}
	if (!closest_plane)
		return ;
	closest_hit->did_hit = 1;
	closest_hit->hit_point = add_vect(ray.origin,
		multiply_vect(ray.dir, closest_hit->dst));
	closest_hit->normal_dir = soustract_vect(closest_hit->hit_point, closest_plane->pos);
	normalize_vect(&closest_hit->normal_dir);
	closest_hit->color = closest_plane->color;
}