/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   colors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nsalles <nsalles@student.42perpignan.fr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/17 19:34:53 by nsalles           #+#    #+#             */
/*   Updated: 2024/03/11 18:17:59 by nsalles          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

t_color	format_color(char *colors_str)
{
	char	**color_split;
	t_color	color;

	color_split = ft_split(colors_str, ',');
	color.r = ft_atoi(color_split[0]);	
	color.g = ft_atoi(color_split[1]);	
	color.b = ft_atoi(color_split[2]);
	free_double_array(color_split);
	return (color);
}

int	color_to_int(t_color color)
{
	return ((color.r << 16) | (color.g << 8) | color.b);
}

t_color	int_to_rgb(int color)
{
	int		r;
	int		g;
	int		b;
	t_color	res;

	b = color & 0xff;
	g = (color & 0x00ff00) >> 8;
	r = color >> 16;
	
	res.b = b;
	res.g = g;
	res.r = r;
	return (res);
}

void	protect_colors(t_color *color)
{
	if (color->r > 255)
		color->r = 255;
	if (color->g > 255)
		color->g = 255;
	if (color->b > 255)
		color->b = 255;
}

t_color	multiplies_color(t_color color, double factor)
{
	color.r *= factor;
	color.g *= factor;
	color.b *= factor;
	return (color);
}

t_color	combine_colors(t_color color, t_color reflective, double ratio)
{
	t_color	res;

	ratio *= 0.5;
	res.r = color.r * (1.0 - ratio) + reflective.r * ratio;
	res.g = color.g * (1.0 - ratio) + reflective.g * ratio;
	res.b = color.b * (1.0 - ratio) + reflective.b * ratio;
	protect_colors(&res);
	return (res);
}
