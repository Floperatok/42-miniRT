/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cylinders.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nsalles <nsalles@student.42perpignan.fr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/27 14:45:11 by nsalles           #+#    #+#             */
/*   Updated: 2024/03/20 16:53:09 by nsalles          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

/*
 *	Precomputes basic values for Cylinder ray intersection.
 *	Having to initiaze such structure is ugly but it's the better way to 
 *	follow the 42 norm (which prohibits the use of more than 5 variables in 
 *	one function) and don't having to compute values more than one time. 
*/
static t_cy_values	precompute_cylinder_values(t_ray ray, t_cylinder *cy)
{
	t_cy_values	val;

	val.oc = soustract_vect(ray.origin, cy->a);
	val.bard = dot(cy->ba, ray.dir);
	val.baoc = dot(cy->ba, val.oc);
	val.k2 = cy->baba - val.bard * val.bard;
	val.k1 = cy->baba * dot(val.oc, ray.dir) - val.baoc * val.bard;
	val.k0 = cy->baba * dot(val.oc, val.oc) - val.baoc * val.baoc - \
		cy->radius * cy->radius * cy->baba;
	val.discr = val.k1 * val.k1 - val.k2 * val.k0;
	return (val);
}

/*
 *	Returns the normal vector of the point on the body of the cylinder.
 *	Thanks to https://www.shadertoy.com/view/4lcSRn and 
 *	https://iquilezles.org/articles/intersectors/ for the formula.
*/
t_vec	cylinder_normal(t_cylinder *cy, t_vec hitpos, double y, int is_cap)
{
	t_vec	normal;
	t_vec	pa;
	
	if (is_cap)
		normal = divide_vect(multiply_vect(cy->ba, sign(y)), 
			sqrt(cy->baba));
	else
	{
		pa = soustract_vect(hitpos, cy->a);
		normal = divide_vect(soustract_vect(pa, 
			multiply_vect(cy->ba, (dot(pa, cy->ba) / cy->baba))), cy->radius);	
	}
	return (normal);
}

/*
 *	Detects whether the ray encounters a sphere. If it does, returns the
 *	distance of the sphere. Else returns -1.
 *	If the ray hits one of the caps, set the normal vector accordingly,
 *	else NULL.
 *	Thanks to https://www.shadertoy.com/view/4lcSRn and 
 *	https://iquilezles.org/articles/intersectors/ for the formula.
*/
static t_cy_values one_cylinder_intersection(t_ray ray, t_cylinder *cy)
{
	t_cy_values	val;

	val = precompute_cylinder_values(ray, cy);
	val.dst = -1;
	if (val.discr < 0)
		return (val);
	val.discr = sqrt(val.discr);
	val.dst = (-val.k1 - val.discr) / val.k2;
	val.y = val.baoc + val.dst * val.bard;
	val.is_cap = 0;
	if (val.y > 0 && val.y < cy->baba)
		return (val);
	val.is_cap = 1;
	if (val.y < 0.0)
		val.dst = (0.0 - val.baoc) / val.bard;
	else
		val.dst = (cy->baba - val.baoc) / val.bard;
	if (fabs(val.k1 + val.k2 * val.dst) >= val.discr)
		val.dst = -1;
	return (val);
}

void	cylinders_intersection(t_ray ray, t_cylinder **cylinders,
	t_hitinfo *closest_hit)
{
	t_cylinder	*closest_cy;
	t_cy_values	val;
	t_cy_values	val_closest_cy;
	int			i;

	val_closest_cy.dst = -1;
	i = -1;
	while (cylinders[++i])
	{
		val = one_cylinder_intersection(ray, cylinders[i]);
		if (val.dst > 0.0 && val.dst < closest_hit->dst)
		{
			closest_cy = cylinders[i];
			val_closest_cy = val;
			closest_hit->dst = val.dst;
		}
	}
	if (val_closest_cy.dst == -1)
		return ;
	closest_hit->did_hit = 1;
	closest_hit->color = closest_cy->color;
	closest_hit->dst = val_closest_cy.dst;
	closest_hit->pos = add_vect(ray.origin, multiply_vect(ray.dir, val_closest_cy.dst));
	closest_hit->reflect_ratio = closest_cy->reflect_ratio;
	closest_hit->normal = cylinder_normal(closest_cy, closest_hit->pos, val_closest_cy.y, val_closest_cy.is_cap);
	closest_hit->specular = closest_cy->specular;
}
