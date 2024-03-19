/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rgb.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: drenassi <@student.42perpignan.fr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/15 20:08:42 by drenassi          #+#    #+#             */
/*   Updated: 2024/03/09 17:21:29 by drenassi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

/*
 *	Returns 1 if the input string has a color format of the form 255,255,255
 *	of 0 if not.
*/
int	check_rgb(char *param)
{
	int		i;
	int		j;
	int		commas;
	char	*num;

	commas = 0;
	i = 0;
	while (param[i] && param[i] != ' ')
		if (param[i++] == ',')
			commas++;
	if (commas != 2)
		return (0);
	i = 0;
	while (i < (int) ft_strlen(param) && param[i] && param[i] != ' ')
	{
		j = 0;
		while (param[j] && param[j] != ',')
			j++;
		num = ft_substr(param, i, j);
		if (ft_atoi(num) < 0 || ft_atoi(num) > 255)
			return (free(num), 0);
		free(num);
		i += j + 1;
	}
	return (1);
}
