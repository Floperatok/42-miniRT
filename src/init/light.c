/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   light.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nsalles <nsalles@student.42perpignan.fr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/24 14:04:12 by nsalles           #+#    #+#             */
/*   Updated: 2024/02/24 15:18:32 by nsalles          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

void	get_light(char ***objs, t_light *light)
{
	int		i;

	i = 0;
	while (objs[i] && ft_strcmp(objs[i][0], "L"))
		i++;
	if (!objs[i])
		return ;
	light->pos = get_point_from_string(objs[i][1], ',');
	light->brightness = ft_atod(objs[i][2]);
	light->color = format_color(objs[i][3]);
}
