/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   reflection.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: drenassi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/22 11:55:33 by drenassi          #+#    #+#             */
/*   Updated: 2024/02/22 11:56:09 by drenassi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

/*
*	Returns the direction of the reflected ray.
*/
t_point	reflection_dir(t_point normal, t_point dir)
{
	t_point		reflection;
	double		scalar;

	scalar = vector_scalar_product(dir, normal);
	reflection.x = 2 * scalar * normal.x - dir.x;
	reflection.y = 2 * scalar * normal.y - dir.y;
	reflection.z = 2 * scalar * normal.z - dir.z;
	return (reflection);
}

/*
*	Returns the reflection color of a given color according to a reflect ratio.
*/
t_color	reflection_color(t_color color, t_color reflective, double ratio)
{
	t_color	res;

	res.r = color.r * (1 - ratio) + reflective.r * ratio;
	res.g = color.g * (1 - ratio) + reflective.g * ratio;
	res.b = color.b * (1 - ratio) + reflective.b * ratio;
	protect_colors(&res);
	res.sum = res.r + res.g + res.b;
	return (res);
}
