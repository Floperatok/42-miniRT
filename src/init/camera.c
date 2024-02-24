/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   camera.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nsalles <nsalles@student.42perpignan.fr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/24 13:53:22 by nsalles           #+#    #+#             */
/*   Updated: 2024/02/24 15:17:57 by nsalles          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

void	get_camera(char ***objs, t_camera *camera)
{
	int			i;

	i = 0;
	while (objs[i] && ft_strcmp(objs[i][0], "C"))
		i++;
	if (!objs[i])
		return ;
	camera->pos = get_point_from_string(objs[i][1], ',');
	camera->direction = get_point_from_string(objs[i][2], ',');
	camera->fov = ft_atoi(objs[i][3]);
}
