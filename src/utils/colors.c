/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   colors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: drenassi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/17 19:34:53 by nsalles           #+#    #+#             */
/*   Updated: 2024/02/19 20:16:56 by drenassi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

int	format_color(char *colors_str)
{
	char	**colors;
	int		r;
	int		g;
	int		b;

	colors = ft_split(colors_str, ',');
	r = ft_atoi(colors[0]);	
	g = ft_atoi(colors[1]);	
	b = ft_atoi(colors[2]);
	free_double_array(colors);
	return ((r << 16) | (g << 8) | b);
}

int		rgb_to_int(int r, int g, int b)
{
	return ((r << 16) | (g << 8) | b);
}

t_color	int_to_rgb(int color)
{
	int		r;
	int		g;
	int		b;
	t_color	res;

	b = color & 0x0000ff;
	g = (color & 0x00ff00) >> 8;
	r = color >> 16;
	
	res.b = b;
	res.g = g;
	res.r = r;
	return (res);
}
