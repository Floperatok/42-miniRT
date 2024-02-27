/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ambient_lightning.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nsalles <nsalles@student.42perpignan.fr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/24 13:46:07 by nsalles           #+#    #+#             */
/*   Updated: 2024/02/27 13:08:17 by nsalles          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

void	destroy_alight(t_alight *alight)
{
	if (alight)
		free(alight);
}

/*
 *	Creates and returns the ambient lightning object if found.
*/
t_alight	*get_alight(char ***objs)
{
	int			i;
	t_alight	*alight;

	i = 0;
	while (objs[i] && ft_strcmp(objs[i][0], "A"))
		i++;
	if (!objs[i])
		return (NULL);
	alight = malloc(sizeof(t_alight));
	alight->ratio = ft_atod(objs[i][1]);
	alight->color = format_color(objs[i][2]);
	return (alight);
}
