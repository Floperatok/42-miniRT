/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cylinders.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nsalles <nsalles@student.42perpignan.fr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/27 14:45:11 by nsalles           #+#    #+#             */
/*   Updated: 2024/02/27 18:54:45 by nsalles          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

static t_hitinfo	one_cylinder_collision(t_ray ray, t_cylinder *cylinder)
{
	t_hitinfo	hitinfo;

	(void)ray;
	(void)cylinder;
	hitinfo.did_hit = 0; // Todo
	return (hitinfo);
}

void	cylinders_collision(t_ray ray, t_cylinder **cylinders, 
	t_hitinfo *closest_hit)
{
	t_hitinfo	cylinder_hitinfo;
	int	i;

	i = -1;
	while (cylinders[++i])
	{
		cylinder_hitinfo = one_cylinder_collision(ray, cylinders[i]);
		if (cylinder_hitinfo.did_hit && cylinder_hitinfo.dst < closest_hit->dst)
			*closest_hit = cylinder_hitinfo;
	}
}
