/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_pixels.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: drenassi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/22 11:58:06 by drenassi          #+#    #+#             */
/*   Updated: 2024/02/22 11:58:26 by drenassi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

/*
*	Draws a pixel in a given color at (x, y) coordinates.
*/
void	draw_pixels(t_image *img, int x, int y, int color)
{
	unsigned int	*pixel;

	pixel = (unsigned int *)(img->addr + (y * img->line_length + \
	x * (img->bits_per_pixel / 8)));
	*pixel = color;
}
