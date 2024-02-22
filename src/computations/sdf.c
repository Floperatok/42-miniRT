/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sdf.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: drenassi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/19 15:19:16 by nsalles           #+#    #+#             */
/*   Updated: 2024/02/22 12:08:12 by drenassi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

// double	sd_sphere(t_point vect, double radius)
// {
// 	return (get_vect_norm(vect) - radius);
// }

// double	detect_shapes(t_data *data, t_image *img, t_point *ray, t_point *pixel)
// {
// 	double	distance;
// 	double	distance2;
// 	double	min_dist;

// 	distance = sd_sphere(substract_vect(*ray, *data->spheres->pos), data->spheres->radius);
// 	distance2 = sd_sphere(substract_vect(*ray, *data->spheres->next->pos), data->spheres->next->radius);
// 	min_dist = fmin(distance, distance2);
// 	if (distance <= 0 && distance <= distance2)
// 	{
// 		pixel_put(img, pixel->x, pixel->y, data->spheres->color);
// 		return (-1);
// 	}
// 	if (distance2 <= 0 && distance2 <= distance)
// 	{
// 		pixel_put(img, pixel->x, pixel->y, data->spheres->next->color);
// 		return (-1);
// 	}
// 	return (min_dist);
// }
