/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   colors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nsalles <nsalles@student.42perpignan.fr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/17 19:34:53 by nsalles           #+#    #+#             */
/*   Updated: 2024/02/17 19:47:09 by nsalles          ###   ########.fr       */
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
