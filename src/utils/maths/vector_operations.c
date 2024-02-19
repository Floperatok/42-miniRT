/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector_operations.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nsalles <nsalles@student.42perpignan.fr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/18 02:58:25 by nsalles           #+#    #+#             */
/*   Updated: 2024/02/19 02:04:39 by nsalles          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

double ft_lenght(t_point vect)
{
	return (sqrt(vect.x * vect.x + vect.y * vect.y + vect.z * vect.z));
}

/*
 *	Multiplies a vector by a scalar.
*/
void	vect_multiply(t_point *vect, double scalar)
{
	vect->x *= scalar;
	vect->y *= scalar;
	vect->z *= scalar;
}

/*
 *	Soustract the components of the first vector by the components of 
 *	the second. Return the result.
*/
t_point	soustract_vect(t_point vect1, t_point vect2)
{
	t_point res;

	res.x = vect1.x - vect2.x;
	res.y = vect1.y - vect2.y;
	res.z = vect1.z - vect2.z;
	return (res);
}

/*
 *	Expand the magnitude of the vector by the normalized vector components.
*/
void	expand_vect(t_point *vect, t_point normalized_vect)
{
	vect->x += normalized_vect.x;
	vect->y += normalized_vect.y;
	vect->z += normalized_vect.z;
}

void	normalize_vect(t_point *vect)
{
	double	lenght;

	lenght = ft_lenght(*vect);
	vect->x /= lenght;
	vect->y /= lenght;
	vect->z /= lenght;
}

t_point	copy_vect(t_point vect)
{
	t_point copy;

	copy.x = vect.x;
	copy.y = vect.y;
	copy.z = vect.z;
	return (copy);
}

void	print_vect(t_point vect)
{
	printf("x = %f ; y = %f ; z = %f\n", vect.x, vect.y, vect.z);
}
