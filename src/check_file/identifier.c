/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   identifier.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: drenassi <@student.42perpignan.fr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/16 22:01:17 by drenassi          #+#    #+#             */
/*   Updated: 2024/03/17 21:18:41 by drenassi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

/*
 *	Returns 1 if a line starts with an existing identifier, 0 if not.
*/
int	check_identifier(char *line)
{
	char	**data;

	data = create_data_array(line);
	if (!ft_strcmp(data[0], "A"))
		return (free_double_array(data), 1);
	else if (!ft_strcmp(data[0], "C"))
		return (free_double_array(data), 1);
	else if (!ft_strcmp(data[0], "L"))
		return (free_double_array(data), 1);
	else if (!ft_strcmp(data[0], "sp"))
		return (free_double_array(data), 1);
	else if (!ft_strcmp(data[0], "pl"))
		return (free_double_array(data), 1);
	else if (!ft_strcmp(data[0], "cy"))
		return (free_double_array(data), 1);
	else if (!ft_strcmp(data[0], "co"))
		return (free_double_array(data), 1);
	print_error("Error: Wrong identifier. List of valid identifiers:\n");
	print_error("A for Ambient lightning;\nC for Camera;\nL for Light;\n");
	print_error("sp for Sphere;\npl for Plane;\ncy for Cylinder.\n");
	print_error("co for Cone.\n");
	return (free_double_array(data), 0);
}
