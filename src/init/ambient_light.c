/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ambient_light.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nsalles <nsalles@student.42perpignan.fr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/17 13:59:15 by nsalles           #+#    #+#             */
/*   Updated: 2024/02/17 16:10:32 by nsalles          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

/*
 *	Ambient lightning struct destroyer.
*/
void	destroy_alight(t_alight *alight)
{
	if (!alight)
		return ;
	free(alight);
}

/*
 *	Create and return ambient lightning struct.
*/
t_alight	*get_alight(double brightness, int color)
{
	t_alight	*alight;

	alight = malloc(sizeof(t_alight));
	if (!alight)
	{
		print_error("Fatal error: ambient lightning struct initialization: ");
		print_error("Out of memory\n");
		return (NULL);
	}
	alight->brightness = brightness;
	alight->color = color;
	return (alight);
}