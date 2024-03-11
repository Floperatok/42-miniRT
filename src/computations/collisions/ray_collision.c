/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_collision.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nsalles <nsalles@student.42perpignan.fr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/27 14:36:23 by nsalles           #+#    #+#             */
/*   Updated: 2024/03/11 17:54:07 by nsalles          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

t_ray	bounce_ray(t_point dir, t_point normal_dir, t_point hit_pos)
{
	t_ray	ray;
	double	doted;

	doted = dot(dir, normal_dir);
	ray.origin = hit_pos;
	ray.dir = soustract_vect(dir, multiply_vect(normal_dir, 2 * doted));
	return (ray);
}

t_hitinfo	ray_collision(t_ray ray, t_objects *objs)
{
	t_hitinfo	closest_hit;

	closest_hit.did_hit = 0;
	closest_hit.dst = INFINITY;
	spheres_collision(ray, objs->spheres, &closest_hit);
	planes_collision(ray, objs->planes, &closest_hit);
	cylinders_collision(ray, objs->cylinders, &closest_hit);
	return (closest_hit);
}
