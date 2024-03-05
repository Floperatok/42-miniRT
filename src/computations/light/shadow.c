/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shadow.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nsalles <nsalles@student.42perpignan.fr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/05 15:51:24 by nsalles           #+#    #+#             */
/*   Updated: 2024/03/05 16:21:49 by nsalles          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

/*
 *	Returns whether or not there is objects between the start_pos and the light.
*/
int	is_in_shadow(t_point start_pos, t_point light_dir, t_objects *objs)
{
	t_ray		ray;
	t_hitinfo	hit;

	ray.dir = light_dir;
	ray.origin = start_pos;
	hit = ray_collision(ray, objs);
	return (hit.did_hit);
}
