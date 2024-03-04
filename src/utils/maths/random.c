/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   random.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nsalles <nsalles@student.42perpignan.fr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/27 16:25:55 by nsalles           #+#    #+#             */
/*   Updated: 2024/02/27 16:26:01 by nsalles          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

double	ft_random(unsigned int *seed)
{
	unsigned int result;
	unsigned int x;

	x = *seed;
	x = x * 747796405 + 2891336453;
	result = ((x >> ((x >> 28) + 4)) ^ x) * 277803737;
	result = (result >> 22) ^ result;
	*seed = result;
	return (result / 4294967295.0);
}
