/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   spheres.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nsalles <nsalles@student.42perpignan.fr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/27 14:18:44 by nsalles           #+#    #+#             */
/*   Updated: 2024/02/27 14:51:31 by nsalles          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

/*
 *	Detects whether the ray encounters a sphere. If it does, returns a
 *	hit_info struct with the distance and the position of the 
 *	intersection point. Else returns a blank hit_info struct.
*/
static t_hitinfo	one_sphere_collision(t_ray ray, t_sphere *sphere)
{
	t_point 	offset_ray;
	double		a;
	double		b;
	double		discriminant;
	t_hitinfo	hitinfo;

	hitinfo.did_hit = 0;
	offset_ray = soustract_vect(ray.origin, sphere->pos);
	a = dot(ray.dir, ray.dir);
	b = 2 * dot(offset_ray, ray.dir);
	discriminant = b * b - 4 * a *
		(dot(offset_ray, offset_ray) - sphere->radius * sphere->radius);
	if (discriminant >= 0)
	{
		hitinfo.dst = (-b - sqrt(discriminant)) / (2 * a);
		if (hitinfo.dst >= 0)
		{
			hitinfo.did_hit = 1;
			hitinfo.hit_point = add_vect(ray.origin,
				multiply_vect(ray.dir, hitinfo.dst));
			hitinfo.color = sphere->color;
		}
	}
	return (hitinfo);
}

/*
 *	Detects whether the ray encounters one of the spheres. 
 *	If it does and the distance of the closest sphere encountered is less
 *	than hitinfo.dst, overwrite the hitinfo infos with the distance and the  
 *	position of the intersection point of the ray with the closest sphere.
 *	If no sphere are encountered, does not change hit_info.
*/
void	spheres_collision(t_ray ray, t_sphere **spheres, t_hitinfo *closest_hit)
{
	t_hitinfo	sphere_hitinfo;
	int	i;

	i = -1;
	while (spheres[++i])
	{
		sphere_hitinfo = one_sphere_collision(ray, spheres[i]);
		if (sphere_hitinfo.did_hit && sphere_hitinfo.dst < closest_hit->dst)
			*closest_hit = sphere_hitinfo;
	}
}