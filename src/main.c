/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: drenassi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/15 12:38:38 by nsalles           #+#    #+#             */
/*   Updated: 2024/02/16 21:53:25 by drenassi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

int main(int ac, char **av)
{
	if (ac != 2)
		return (print_error("Error: One argument needed.\n"), 1);
	if (!check_file(av[1]))
		return (1);
	return (0);
}
