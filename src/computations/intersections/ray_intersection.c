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
