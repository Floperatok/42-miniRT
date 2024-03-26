/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector_operations.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nsalles <nsalles@student.42perpignan.fr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/18 02:58:25 by nsalles           #+#    #+#             */
/*   Updated: 2024/03/26 15:13:39 by nsalles          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

double ft_length(t_vec vect)
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
	t_vec res;

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

/*
 *	Normalize the vector.
*/
t_vec	normalize(t_vec vect)
{
	double	length;

	length = ft_length(vect);
	if (!length)
		return ((t_vec){0, 0, 0});
	vect.x /= length;
	vect.y /= length;
	vect.z /= length;
	return (vect);
}

t_vec	copy_vect(t_vec vect)
{
	t_vec copy;

	copy.x = vect.x;
	copy.y = vect.y;
	copy.z = vect.z;
	return (copy);
}

t_vec	get_vect(double x, double y, double z)
{
	t_vec	vect;

	vect.x = x;
	vect.y = y;
	vect.z = z;
	return (vect);
}

t_vec cross_product(t_vec vect1, t_vec vect2)
{
    t_vec	res;

    res.x = vect1.y * vect2.z - vect1.z * vect2.y;
    res.y = vect1.z * vect2.x - vect1.x * vect2.z;
    res.z = vect1.x * vect2.y - vect1.y * vect2.x;
    return (res);
}

double	dot(t_vec vect1, t_vec vect2)
{
    return (vect1.x * vect2.x + vect1.y * vect2.y + vect1.z * vect2.z);
}

void	print_vect(char *msg, t_vec vect)
{
	printf("%sx = %f ; y = %f ; z = %f\n", msg, vect.x, vect.y, vect.z);
}

t_vec	vect_max(t_vec vect, double n)
{
	if (vect.x > n)
		vect.x = n;
	if (vect.y > n)
		vect.y = n;
	if (vect.z > n)
		vect.z = n;
	return (vect);
}

t_vec	reflect(t_vec dir, t_vec normal)
{
	return (soustract_vect(dir, multiply_vect(normal, 2 * dot(dir, normal))));
}
