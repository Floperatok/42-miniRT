/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atod.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: drenassi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/15 20:46:36 by drenassi          #+#    #+#             */
/*   Updated: 2024/02/18 12:26:57 by drenassi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

static int	ft_atoi_len(char *str)
{
	int	i;

	i = 0;
	while ((str[i] >= 9 && str[i] <= 13) || (str[i] == ' '))
		i++;
	if (str[i] == '+' || str[i] == '-')
		i++;
	while (ft_isdigit(str[i]))
		i++;
	return (i);
}

static int	decimal_len(int n)
{
	int	i;

	i = 0;
	while (n != 0)
	{
		n /= 10;
		i++;
	}
	return (i);
}

double	ft_atod(char *str)
{
	double	dec;
	double	frac;
	int		i;
	int		frac_len;

	dec = ft_atoi(str);
	i = ft_atoi_len(str);
	frac = 0;
	frac_len = 0;
	if (str[i] == '.' && ft_isdigit(str[i + 1]))
	{
		frac = ft_atoi(str + i + 1);
		while (str[++i] == '0')
			frac_len++;
		frac_len += decimal_len(frac);
		frac /= pow(10, frac_len);
	}
	if (dec >= 0)
		return (dec + frac);
	else
		return (dec - frac);
}
