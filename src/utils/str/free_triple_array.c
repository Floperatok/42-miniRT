/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_triple_array.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nsalles <nsalles@student.42perpignan.fr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/24 13:40:28 by nsalles           #+#    #+#             */
/*   Updated: 2024/02/24 13:41:24 by nsalles          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

void	free_triple_array(char ***array)
{
	int	i;

	i = -1;
	while (array[++i])
		free_double_array(array[i]);
	free(array);
}
