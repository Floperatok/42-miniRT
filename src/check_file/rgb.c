/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rgb.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: drenassi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/15 20:08:42 by drenassi          #+#    #+#             */
/*   Updated: 2024/02/15 20:09:06 by drenassi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

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
	while(i < (int) ft_strlen(param) && param[i] && param[i] != ' ')
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