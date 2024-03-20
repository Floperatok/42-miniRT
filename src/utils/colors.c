/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   colors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nsalles <nsalles@student.42perpignan.fr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/17 19:34:53 by nsalles           #+#    #+#             */
/*   Updated: 2024/03/20 20:01:32 by nsalles          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

t_color	format_color(char *colors_str)
{
	char	**color_split;
	t_color	color;

	color_split = ft_split(colors_str, ',');
	color.r = (double)(ft_atoi(color_split[0])) / 255;	
	color.g = (double)(ft_atoi(color_split[1])) / 255;
	color.b = (double)(ft_atoi(color_split[2])) / 255;
	free_double_array(color_split);
	return (color);
}

int	color_to_int(t_color color)
{
	return ((int)(255 * color.r) << 16) | ((int)(255 * color.g) << 8) | (int)(255 * color.b);
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
	
	res.b = b / 255;
	res.g = g / 255;
	res.r = r / 255;
	return (res);
}

void	protect_colors(t_color *color)
{
	if (color->r > 1)
		color->r = 1;
	if (color->g > 1)
		color->g = 1;
	if (color->b > 1)
		color->b = 1;
	if (color->r < 0)
		color->r = 0;
	if (color->g < 0)
		color->g = 0;
	if (color->b < 0)
		color->b = 0;

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

	res.r = color.r * (1.0 - ratio) + reflective.r * ratio;
	res.g = color.g * (1.0 - ratio) + reflective.g * ratio;
	res.b = color.b * (1.0 - ratio) + reflective.b * ratio;
	protect_colors(&res);
	return (res);
}
