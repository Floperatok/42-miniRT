/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   planes.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nsalles <nsalles@student.42perpignan.fr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/27 14:37:05 by nsalles           #+#    #+#             */
/*   Updated: 2024/02/27 14:56:35 by nsalles          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

/*
 *	Detects whether the ray encounters a plane. If it does, returns a
 *	hit_info struct with the distance and the position of the 
 *	intersection point. Else returns a blank hit_info struct.
*/
static t_hitinfo	one_plane_collision(t_ray ray, t_plane *plane)
{
	t_hitinfo	hitinfo;

	(void)ray;
	(void)plane;
	hitinfo.did_hit = 0; // Todo
	return (hitinfo);
}

/*
 *	Detects whether the ray encounters one of the planes. 
 *	If it does and the distance of the closest plane encountered is less
 *	than hitinfo.dst, overwrite the hitinfo infos with the distance and the  
 *	position of the intersection point of the ray with the closest plane.
 *	If no plane are encountered, does not change hit_info.
*/
void	planes_collision(t_ray ray, t_plane **planes, t_hitinfo *closest_hit)
{
	t_hitinfo	plane_hitinfo;
	int	i;

	i = -1;
	while (planes[++i])
	{
		plane_hitinfo = one_plane_collision(ray, planes[i]);
		if (plane_hitinfo.did_hit && plane_hitinfo.dst < closest_hit->dst)
			*closest_hit = plane_hitinfo;
	}
}