/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_collision.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nsalles <nsalles@student.42perpignan.fr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/27 14:36:23 by nsalles           #+#    #+#             */
/*   Updated: 2024/02/27 14:57:04 by nsalles          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

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
