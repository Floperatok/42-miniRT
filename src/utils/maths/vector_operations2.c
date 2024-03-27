/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector_operations2.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nsalles <nsalles@student.42perpignan.fr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/27 20:33:23 by nsalles           #+#    #+#             */
/*   Updated: 2024/03/27 20:37:02 by nsalles          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

t_vec	cross_product(t_vec vect1, t_vec vect2)
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
