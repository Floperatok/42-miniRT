/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector_operations.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nsalles <nsalles@student.42perpignan.fr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/18 02:58:25 by nsalles           #+#    #+#             */
/*   Updated: 2024/03/27 20:37:19 by nsalles          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

double	ft_length(t_vec vect)
{
	return (sqrt(vect.x * vect.x + vect.y * vect.y + vect.z * vect.z));
}

/*
 *	Multiplies a vector by a scalar and returns the result.
*/
t_vec	multiply_vect(t_vec vect, double scalar)
{
	vect.x *= scalar;
	vect.y *= scalar;
	vect.z *= scalar;
	return (vect);
}

t_vec	divide_vect(t_vec vect, double scalar)
{
	vect.x /= scalar;
	vect.y /= scalar;
	vect.z /= scalar;
	return (vect);
}

/*
 *	Subtracts the components of the first vector by the components of 
 *	the second and returns the result.
*/
t_vec	soustract_vect(t_vec vect1, t_vec vect2)
{
	t_vec	res;

	res.x = vect1.x - vect2.x;
	res.y = vect1.y - vect2.y;
	res.z = vect1.z - vect2.z;
	return (res);
}

/*
 *	Adds the second vector to the first and returns the result.
*/
t_vec	add_vect(t_vec vect1, t_vec vect2)
{
	vect1.x += vect2.x;
	vect1.y += vect2.y;
	vect1.z += vect2.z;
	return (vect1);
}
