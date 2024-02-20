/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   loading_display.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nsalles <nsalles@student.42perpignan.fr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/19 16:10:53 by nsalles           #+#    #+#             */
/*   Updated: 2024/02/19 16:59:48 by nsalles          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

/*
 *	Display a loading message, the percentages are calculated with the start,
 *	the position and the percent size.
*/
void	display_loading(char *msg, int start, int pos, int percent_size)
{
	int			percent;
	static int	last = -1;

	percent = (pos - start) / percent_size;
	if (last != percent)
	{
		if (percent == 0)
			ft_printf("%s\t%d%%", msg, percent);
		else if (percent == 100)
		{
			ft_printf("\b\b\b\b\t%d%%\n", percent);
			last = -1;
		}
		else
			ft_printf("\b\b\b\b\t%d%%", percent);
	}
	last = percent;
}