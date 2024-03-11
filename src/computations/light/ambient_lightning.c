/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ambient_lightning.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nsalles <nsalles@student.42perpignan.fr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/04 17:20:00 by nsalles           #+#    #+#             */
/*   Updated: 2024/03/11 14:49:31 by nsalles          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

t_color	apply_ambient_lightning(t_alight *alight, t_color color)
{
	if (!alight)
		return (color);
	color.r *= alight->ratio;
	color.g *= alight->ratio;
	color.b *= alight->ratio;
	return (color);
}
