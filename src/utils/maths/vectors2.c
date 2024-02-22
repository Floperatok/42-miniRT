/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector_operations.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: drenassi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/18 02:58:25 by nsalles           #+#    #+#             */
/*   Updated: 2024/02/22 11:40:37 by drenassi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

/*
 *	Normalize the vector and return the result.
*/
t_point normalize_vect(t_point vect)
{
	t_point	normalized;
	double	norm;

	norm = get_vect_norm(vect);
	normalized.x = vect.x / norm;
	normalized.y = vect.y / norm;
	normalized.z = vect.z / norm;
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
