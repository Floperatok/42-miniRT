/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   camera.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: drenassi <@student.42perpignan.fr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/16 20:31:10 by drenassi          #+#    #+#             */
/*   Updated: 2024/03/09 17:15:04 by drenassi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

/*
 *	Returns 1 if the FOV has the good format in range [0-180], 0 if not.
*/
static int	check_horizontal_field(char *field)
{
	int	i;
	int	value;

	i = 0;
	if (field[i] == '+')
		i++;
	while (field[i])
	{
		if (field[i] < '0' || field[i] > '9')
		{
			print_error("Error: Camera: Horizontal field of view must be ");
			return (print_error("in range [0,180]. Example: 70.\n"));
		}
		i++;
	}
	value = ft_atoi(field);
	if (value < 0 || value > 180)
	{
		print_error("Error: Camera: Horizontal field of view must be ");
		return (print_error("in range [0,180]. Example: 70.\n"));
	}
	return (1);
}

/*
 *	Returns 1 if the cameras' parameters are corrects, 0 if not.
*/
int	check_camera(char **data)
{
	static int	c_count = 0;

	c_count++;
	if (c_count > 1)
		return (print_error("Error: Too much Cameras.\n"));
	if (double_array_len(data) != 4)
		return (print_error("Error: Camera needs 3 arguments.\n"));
	if (!check_coordinates(data[1]))
		return (print_error("Error: Camera: Wrong coordinates.\n"));
	if (!check_orientation_vector(data[2]))
		return (print_error("Error: Camera: Wrong orientation vector. It "),
			print_error("must be in range [-1.0,1.0] for each axis.\n"));
	if (!check_horizontal_field(data[3]))
		return (0);
	return (1);
}
