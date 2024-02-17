/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   camera.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nsalles <nsalles@student.42perpignan.fr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/17 13:29:17 by nsalles           #+#    #+#             */
/*   Updated: 2024/02/17 14:15:51 by nsalles          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

/*
 *	Create and return camera struct.
*/
t_camera	*get_camera(t_point *pos, t_point *direction, int fov)
{
	t_camera	*camera;

	camera = malloc(sizeof(camera));
	if (!camera)
		return (NULL);
	if (!pos || !direction)
	{
		free(camera);
		destroy_point(pos);
		destroy_point(direction);
		return (NULL);
	}
	camera->pos = pos;
	camera->direction = direction;
	camera->fov = fov;
	return (camera);
}

/*
 *	Camera struct destroyer.
*/
void	destroy_camera(t_camera *camera)
{
	if (!camera)
		return ;
	destroy_point(camera->direction);
	destroy_point(camera->pos);
	free(camera);
}