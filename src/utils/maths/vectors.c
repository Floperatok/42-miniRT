/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vectors.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: drenassi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/22 11:33:42 by drenassi          #+#    #+#             */
/*   Updated: 2024/02/22 11:39:45 by drenassi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

/*
*	Returns the norm of the given vector.
*/
double get_vect_norm(t_point vect)
{
	return (sqrt(vect.x * vect.x + vect.y * vect.y + vect.z * vect.z));
}

/*
 *	Adds the second vector to the first and returns the result.
*/
t_point	add_vect(t_point vect1, t_point vect2)
{
	vect1.x += vect2.x;
	vect1.y += vect2.y;
	vect1.z += vect2.z;
	return (vect1);
}

/*
 *	Subtracts the components of the first vector by the components of 
 *	the second and returns the result.
*/
t_point	substract_vect(t_point vect1, t_point vect2)
{
	t_point res;

	res.x = vect1.x - vect2.x;
	res.y = vect1.y - vect2.y;
	res.z = vect1.z - vect2.z;
	return (res);
}

/*
 *	Multiplies a vector by a scalar and returns the result.
*/
t_point	multiply_vect(t_point vect, double scalar)
{
	t_point res;

	res.x = vect.x * scalar;
	res.y = vect.y * scalar;
	res.z = vect.z * scalar;
	return (res);
}

/*
*	Returns the scalar product between 2 vectors.
*/
double	vector_scalar_product(t_point vect1, t_point vect2)
{
	return (vect1.x * vect2.x + vect1.y * vect2.y + vect1.z * vect2.z);
}
