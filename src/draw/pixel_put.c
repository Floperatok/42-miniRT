/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pixel_put.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nsalles <nsalles@student.42perpignan.fr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/16 23:48:57 by nsalles           #+#    #+#             */
/*   Updated: 2024/02/17 00:01:41 by nsalles          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

/*
 *	Write on the image a colored pixel of the coordinate x and y.
 *	Origin is on the top left corner.
 *	Color format : 0xRRGGBB
*/
void	pixel_put(t_image *img, int x, int y, int color)
{
	char	*dst;

	if (x > 0 && x < img->image_width && y > 0 && y < img->image_height)
	{
		dst = (char *)img->addr + (y * img->line_length + x * \
			(img->bits_per_pixel / 8));
		*(unsigned int *)dst = color;
	}
}