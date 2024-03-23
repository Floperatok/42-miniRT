/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   camera.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nsalles <nsalles@student.42perpignan.fr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/24 13:53:22 by nsalles           #+#    #+#             */
/*   Updated: 2024/03/22 12:40:29 by nsalles          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

void	destroy_camera(t_camera *camera)
{
	if (camera)
		free(camera);
}

/*
 *	Creates and returns the camera object if found.
*/
t_camera	*get_camera(char ***objs)
{
	int			i;
	t_camera	*camera;

	i = 0;
	while (objs[i] && ft_strcmp(objs[i][0], "C"))
		i++;
	if (!objs[i])
		return (NULL);
	camera = malloc(sizeof(t_camera));
	camera->pos = get_vec_from_string(objs[i][1], ',');
	camera->dir = get_vec_from_string(objs[i][2], ',');
	camera->fov = ft_atoi(objs[i][3]);
	camera->screen_w = ft_atoi(objs[i][4]);
	camera->screen_h = ft_atoi(objs[i][5]);
	return (camera);
}
