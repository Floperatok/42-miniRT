/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pixel_put.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nsalles <nsalles@student.42perpignan.fr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/16 23:48:57 by nsalles           #+#    #+#             */
/*   Updated: 2024/03/27 20:28:02 by nsalles          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

/*
 *	Write on the image a colored pixel of the coordinate x and y.
 *	Origin is on the top left corner.
 *	Color format : 0xRRGGBB
*/
void	pixel_put(t_image *img, int x, int y, t_color color)
{
	char	*dst;

	if (x > 0 && x < img->width && y > 0 && y < img->height)
	{
		dst = (char *)img->addr + (y * img->line_length + x * 4);
		*(unsigned int *)dst = color_to_int(color);
	}
}
