/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atod.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arawyn <arawyn@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/15 20:46:36 by drenassi          #+#    #+#             */
/*   Updated: 2024/03/13 21:04:03 by arawyn           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

/*
 *	Returns the length of the converted string from an integer.
*/
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

/*
 *	Returns the number of digits of an integer in base 10.
*/
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

/*
 *	Converts a characters string into a double and returns it.
*/
double	ft_atod(char *str)
{
	double	dec;
	double	frac;
	int		i;
	int		frac_len;
	int		sign;

	sign = 1;
	if (str[0] == '-')
		sign = -1;
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
	if (sign > 0)
		return (dec + frac);
	else
		return (dec - frac);
}
