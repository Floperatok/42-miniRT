/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_ratio.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nsalles <nsalles@student.42perpignan.fr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/22 11:43:40 by nsalles           #+#    #+#             */
/*   Updated: 2024/03/22 11:45:26 by nsalles          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

int	check_ratio(char *str)
{
	double	ratio;

	ratio = ft_atod(str);
	return (ratio > 0.0 && ratio < 1.0);
}
