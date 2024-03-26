/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   compute_camera.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nsalles <nsalles@student.42perpignan.fr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/26 13:22:34 by nsalles           #+#    #+#             */
/*   Updated: 2024/03/26 15:54:55 by nsalles          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

/*
 *	Returns the cosinus of the angle formed by two vectors.
*/
double	vect_cos(t_vec v1, t_vec v2)
{
	return (dot(v1, v2) / (ft_length(v1) * ft_length(v2)));
}

/*
 *	Returns the sinus of the angle formed by two vectors.
*/
double	vect_sin(t_vec v1, t_vec v2)
{
	double	sinus;

	sinus = ft_length(cross_product(v1, v2)) \
		/ (ft_length(v1) * ft_length(v2));
	return (sinus);
}

/*
 *	Returns the vector resulting of the rotation of a vector around an axis.
*/
t_vec	rotate_vect(t_vec vector, t_vec axis, double cos, double sin)
{
	t_vec	rotated;

	rotated.x = (axis.x * axis.x * (1 - cos) + cos) * vector.x \
		+ (axis.x * axis.y * (1 - cos) - axis.z * sin) * vector.y \
		+ (axis.x * axis.z * (1 - cos) + axis.y * sin) * vector.z;
	rotated.y = (axis.x * axis.y * (1 - cos) + axis.z * sin) * vector.x \
		+ (axis.y * axis.y * (1 - cos) + cos) * vector.y \
		+ (axis.y * axis.z * (1 - cos) - axis.x * sin) * vector.z;
	rotated.z = (axis.x * axis.z * (1 - cos) - axis.y * sin) * vector.x \
		+ (axis.y * axis.z * (1 - cos) + axis.x * sin) * vector.y \
		+ (axis.z * axis.z * (1 - cos) + cos) * vector.z;
	return (rotated);
}

void	setup_camera(t_camera *cam)
{
	t_vec	axis;
	double	cos;
	double	sin;

	axis = normalize(cross_product(cam->base[2], cam->dir));
	cos = vect_cos(cam->base[2], cam->dir);
	sin = vect_sin(cam->base[2], cam->dir);
	cam->base[0] = normalize(rotate_vect(cam->base[0], axis, cos, sin));
	cam->base[1] = normalize(rotate_vect(cam->base[1], axis, cos, sin));
	cam->base[2] = normalize(rotate_vect(cam->base[2], axis, cos, sin));
	cam->viewport_dst = VIEWPORT_DST;
}
