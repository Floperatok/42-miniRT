/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_input.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nsalles <nsalles@student.42perpignan.fr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/12 17:41:42 by nsalles           #+#    #+#             */
/*   Updated: 2024/03/12 18:05:11 by nsalles          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

/*
 *	Checks the arguments given by the user. The user can optionnally enter the
 *	hardware utilisation for all the computations :
 *	0 : single thread computation.
 *	1 : multiple threads computation.
 *	2 : GPU computation.
 *	Returns 1 if the input format is correct, 0 otherwise. Sets hardware with
 *	the entered value.
*/
int	check_input(int ac, char **av, int *hardware)
{
	if (ac == 3)
	{
		if (!ft_strcmp(av[2], "0"))
			*hardware = 0;
		else if (!ft_strcmp(av[2], "1"))
			*hardware = 1;
		else if (!ft_strcmp(av[2], "2"))
			*hardware = 2;
		else
		{
			print_usage();
			return (0);
		}
		return (1);
	}
	if (ac == 2)
	{
		*hardware = 0;
		return (1);
	}
	else
	{
		print_usage();
		return (0);
	}
}
