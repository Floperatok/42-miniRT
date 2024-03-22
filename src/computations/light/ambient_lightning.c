/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ambient_lightning.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nsalles <nsalles@student.42perpignan.fr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/04 17:20:00 by nsalles           #+#    #+#             */
/*   Updated: 2024/03/21 17:12:50 by nsalles          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

t_color	apply_ambient_lightning(t_alight *alight, t_color color)
{
	if (!alight)
		return (color);
	color.r *= alight->ratio * 0.8;
	color.g *= alight->ratio * 0.8;
	color.b *= alight->ratio * 0.8;
	return (color);
}
