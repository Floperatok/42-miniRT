/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ambient_lightning.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nsalles <nsalles@student.42perpignan.fr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/24 13:46:07 by nsalles           #+#    #+#             */
/*   Updated: 2024/02/24 15:17:15 by nsalles          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

void	get_alight(char ***objs, t_alight *alight)
{
	int			i;

	i = 0;
	while (objs[i] && ft_strcmp(objs[i][0], "A"))
		i++;
	if (!objs[i])
		return ;
	alight->ratio = ft_atod(objs[i][1]);
	alight->color = format_color(objs[i][2]);
}
