/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ambient_lightning.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nsalles <nsalles@student.42perpignan.fr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/04 17:20:00 by nsalles           #+#    #+#             */
/*   Updated: 2024/03/04 17:49:13 by nsalles          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

int	apply_ambient_lightning(t_alight *alight, int color_int)
{
	t_color color;

	if (!alight)
		return (color_int);
	color = int_to_rgb(color_int);
	color.r *= alight->ratio;
	color.g *= alight->ratio;
	color.b *= alight->ratio;
	return (rgb_to_int(color.r, color.g, color.b));
}
