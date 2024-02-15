/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ambiant_lightning.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: drenassi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/15 19:07:50 by drenassi          #+#    #+#             */
/*   Updated: 2024/02/15 19:30:51 by drenassi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

static int	check_rgb(char *param)
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
	while(param[i] && param[i] != ' ')
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

int check_ambiant_lightning(char *line)
{
	int		i;
	char	*rgb;

	i = 1;
	while (line[i] == ' ')
		i++;
	if (line[i] < '0' || line[i] > '1')
		return (print_error("Error: Wrong syntax for Ambient lightning.\n"),
			print_error("Ratio must be in range [0.0,1.0]. Example: 0.2\n"));
	if (line[++i] != '.')
		return (print_error("Error: Wrong syntax for Ambient lightning.\n"),
			print_error("Ratio must be in range [0.0,1.0]. Example: 0.2\n"));
	if (line[++i] < '0' || line[i] > '9')
		return (print_error("Error: Wrong syntax for Ambient lightning.\n"),
			print_error("Ratio must be in range [0.0,1.0]. Example: 0.2\n"));
	i++;
	while (line[i] == ' ')
		i++;
	rgb = ft_substr(line, i, ft_strlen(line) - i);
	if (!check_rgb(rgb))
		return (free(rgb), print_error("Error: Wrong syntax for Ambient "),
			print_error("lighting.\nRGB colors must be in range [0-255].\n"),
			print_error("Example: 255,255,255\n"));
	return (free(rgb), 1);
}
