/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input_handling.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nsalles <nsalles@student.42perpignan.fr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/17 00:49:29 by nsalles           #+#    #+#             */
/*   Updated: 2024/03/27 19:40:50 by nsalles          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

int	user_input(int keycode, t_minirt *data)
{
	if (keycode == 65307)
		exit_handling(data);
	else if (keycode == 32)
	{
		data->an -= 0.02;
		data->objs.camera->pos.x = 5 * cos(data->an);
		data->objs.camera->pos.y = 0;
		data->objs.camera->pos.z = 5 * sin(data->an);
		data->objs.camera->dir = normalize(\
			multiply_vect(data->objs.camera->pos, -1));
		data->objs.camera->pos = multiply_vect(data->objs.camera->pos, 2);
		data->objs.camera->pos.y = 2;
		render(data);
	}
	else
		ft_printf("keycode = %d\n", keycode);
	return (0);
}
