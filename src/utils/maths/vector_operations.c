/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector_operations.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nsalles <nsalles@student.42perpignan.fr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/18 02:58:25 by nsalles           #+#    #+#             */
/*   Updated: 2024/02/20 04:35:46 by nsalles          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

double ft_lenght(t_point vect)
{
	return (sqrt(vect.x * vect.x + vect.y * vect.y + vect.z * vect.z));
}

/*
 *	Multiplies a vector by a scalar and returns the result.
*/
t_point	vect_multiply(t_point *vect, double scalar)
{
	t_point res;

	res.x = vect->x * scalar;
	res.y = vect->y * scalar;
	res.z = vect->z * scalar;
	return (res);
}

/*
 *	Subtracts the components of the first vector by the components of 
 *	the second and returns the result.
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
 *	Normalize the vector and return the result.
*/
t_point normalize_vect(t_point vect)
{
	t_point	normalized;
	double	lenght;

	lenght = ft_lenght(vect);
	normalized.x = vect.x / lenght;
	normalized.y = vect.y / lenght;
	normalized.z = vect.z / lenght;
	return (normalized);
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
