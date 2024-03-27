/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   spheres.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nsalles <nsalles@student.42perpignan.fr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/27 14:18:44 by nsalles           #+#    #+#             */
/*   Updated: 2024/03/27 20:22:06 by nsalles          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

/*
 *	Detects whether the ray encounters a sphere. If it does, returns the
 *	distance of the sphere. Else returns -1.
*/
double	one_sphere_intersection(t_ray ray, t_sphere *sphere)
{
	t_vec	offset_ray;
	double	a;
	double	b;
	double	discriminant;
	double	dst;

	offset_ray = soustract_vect(ray.origin, sphere->pos);
	a = dot(ray.dir, ray.dir);
	b = 2 * dot(offset_ray, ray.dir);
	discriminant = b * b - 4 * a
		* (dot(offset_ray, offset_ray) - sphere->radius * sphere->radius);
	if (discriminant >= 0)
	{
		dst = (-b - sqrt(discriminant)) / (2 * a);
		if (dst >= 0)
			return (dst);
	}
	return (-1);
}

/*
 *	Detects whether the ray encounters one of the spheres. 
 *	If it does and the distance of the closest sphere encountered is less
 *	than hitinfo.dst, overwrite the hitinfo infos with the distance and the  
 *	position of the intersection point of the ray with the closest sphere.
 *	If no sphere are encountered, does not change hit_info.
*/
void	spheres_intersection(t_ray ray, t_sphere **spheres,
	t_hitinfo *closest_hit)
{
	double		dst;
	t_sphere	*closest_sphere;
	int			i;

	closest_sphere = NULL;
	i = -1;
	while (spheres[++i])
	{
		dst = one_sphere_intersection(ray, spheres[i]);
		if (dst != -1 && dst < closest_hit->dst)
		{
			closest_sphere = spheres[i];
			closest_hit->dst = dst;
		}
	}
	if (!closest_sphere)
		return ;
	closest_hit->did_hit = 1;
	closest_hit->pos = add_vect(ray.origin,
			multiply_vect(ray.dir, closest_hit->dst));
	closest_hit->normal = normalize(soustract_vect(closest_hit->pos,
				closest_sphere->pos));
	closest_hit->color = closest_sphere->color;
	closest_hit->reflect_ratio = closest_sphere->reflect_ratio;
	closest_hit->specular = closest_sphere->specular;
}
