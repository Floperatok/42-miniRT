/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   distance.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nsalles <nsalles@student.42perpignan.fr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/18 02:16:44 by nsalles           #+#    #+#             */
/*   Updated: 2024/02/18 16:48:27 by nsalles          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

double ft_distance(t_point vect1, t_point vect2)
{
	return (sqrt(pow(vect1.x - vect2.x, 2) + pow(vect1.y - vect2.y, 2)));
}

