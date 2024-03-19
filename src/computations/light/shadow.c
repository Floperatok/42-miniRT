/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shadow.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nsalles <nsalles@student.42perpignan.fr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/05 15:51:24 by nsalles           #+#    #+#             */
/*   Updated: 2024/03/19 16:36:42 by nsalles          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

/*
 *	Returns whether or not there is objects between the start_pos and the light.
*/
int	is_in_shadow(t_vec start_pos, t_vec light_dir, double light_dst,
	t_objects *objs)
{
	t_ray		ray;
	t_hitinfo	hit;

	ray.dir = light_dir;
	ray.origin = start_pos;
	hit = ray_intersection(ray, objs);
	return (hit.did_hit && hit.dst < light_dst);
}
