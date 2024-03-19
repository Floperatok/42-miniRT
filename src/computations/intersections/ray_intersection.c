/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_intersection.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nsalles <nsalles@student.42perpignan.fr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/27 14:36:23 by nsalles           #+#    #+#             */
/*   Updated: 2024/03/19 16:35:02 by nsalles          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

t_ray	bounce_ray(t_vec dir, t_vec normal_dir, t_vec hit_pos)
{
	t_ray	ray;
	double	doted;

	doted = dot(dir, normal_dir);
	ray.origin = hit_pos;
	ray.dir = soustract_vect(dir, multiply_vect(normal_dir, 2 * doted));
	return (ray);
}

t_hitinfo	ray_intersection(t_ray ray, t_objects *objs)
{
	t_hitinfo	closest_hit;

	closest_hit.did_hit = 0;
	closest_hit.dst = INFINITY;
	spheres_intersection(ray, objs->spheres, &closest_hit);
	planes_intersection(ray, objs->planes, &closest_hit);
	cylinders_intersection(ray, objs->cylinders, &closest_hit);
	return (closest_hit);
}
