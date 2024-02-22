/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   intersections.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: drenassi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/22 11:41:55 by drenassi          #+#    #+#             */
/*   Updated: 2024/02/22 11:42:11 by drenassi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

/*
*	Returns the minimum solution of the quadratic equation, or min if both
*	values are smaller.
*/
double	quadratic_min(double a, double b, double c, double min)
{
	double	x;
	double	y;
	double	delta;

	delta = b * b - 4 * a * c;
	if (delta < 0)
		return (INFINITY);
	delta = sqrt(delta);
	x = (-b - delta) / (2 * a);
	y = (-b + delta) / (2 * a);
	if (x < y && x > min)
		return (x);
	else if (y > min)
		return (y);
	else
		return (INFINITY);
}
