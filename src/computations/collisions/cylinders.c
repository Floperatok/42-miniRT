/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cylinders.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nsalles <nsalles@student.42perpignan.fr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/27 14:45:11 by nsalles           #+#    #+#             */
/*   Updated: 2024/02/27 14:56:21 by nsalles          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

/*
 *	Detects whether the ray encounters a cylinder. If it does, returns a
 *	hit_info struct with the distance and the position of the 
 *	intersection point. Else returns a blank hit_info struct.
*/
static t_hitinfo	one_cylinder_collision(t_ray ray, t_cylinder *cylinder)
{
	t_hitinfo	hitinfo;

	(void)ray;
	(void)cylinder;
	hitinfo.did_hit = 0; // Todo
	return (hitinfo);
}

/*
 *	Detects whether the ray encounters one of the cylinders. 
 *	If it does and the distance of the closest cylinder encountered is less
 *	than hitinfo.dst, overwrite the hitinfo infos with the distance and the  
 *	position of the intersection point of the ray with the closest cylinder.
 *	If no cylinder are encountered, does not change hit_info.
*/
void	cylinders_collision(t_ray ray, t_cylinder **cylinders, 
	t_hitinfo *closest_hit)
{
	t_hitinfo	cylinder_hitinfo;
	int	i;

	i = -1;
	while (cylinders[++i])
	{
		cylinder_hitinfo = one_cylinder_collision(ray, cylinders[i]);
		if (cylinder_hitinfo.did_hit && cylinder_hitinfo.dst < closest_hit->dst)
			*closest_hit = cylinder_hitinfo;
	}
}
