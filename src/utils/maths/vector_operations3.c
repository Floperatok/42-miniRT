/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector_operations3.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nsalles <nsalles@student.42perpignan.fr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/27 20:34:13 by nsalles           #+#    #+#             */
/*   Updated: 2024/03/27 20:37:29 by nsalles          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

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
	t_vec	copy;

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
