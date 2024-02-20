/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cylinder.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: drenassi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/17 13:54:10 by nsalles           #+#    #+#             */
/*   Updated: 2024/02/20 13:59:48 by drenassi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

/*
 *	Cylinder struct destroyer.
*/
static void	destroy_one_cylinder(t_cylinder *cylinder)
{
	if (!cylinder)
		return ;
	destroy_point(cylinder->pos);
	destroy_point(cylinder->vector);
	free(cylinder);
}

void	destroy_cylinder(t_cylinder **cylinder)
{
	t_cylinder	*tmp;

	if (!cylinder)
		return ;
	tmp = *cylinder;
	while (*cylinder)
	{
		tmp = (*cylinder)->next;
		destroy_one_cylinder(*cylinder);
		*cylinder = tmp;
	}
	cylinder = NULL;
}

/*
 *	Create, set the values and return cylinder struct.
*/
static t_cylinder	*new_cylinder(t_point *pos_vect[2], double rad_height[2], int clr)
{
	t_cylinder	*cylinder;

	cylinder = ft_calloc(1, sizeof(t_cylinder));
	if (!cylinder)
	{
		print_error("Fatal error: cylinder struct initialization: ");
		print_error("Out of memory\n");
		return (NULL);
	}
	if (!pos_vect[0] || !pos_vect[1])
	{
		free(cylinder);
		destroy_point(pos_vect[0]);
		destroy_point(pos_vect[1]);
		return (NULL);
	}
	cylinder->pos = pos_vect[0];
	cylinder->vector = pos_vect[1];
	cylinder->radius = rad_height[0];
	cylinder->height = rad_height[1];
	cylinder->color = clr;
	cylinder->next = NULL;
	return (cylinder);
}

static t_cylinder	*get_last_cylinder(t_cylinder *cylinder)
{
	if (!cylinder)
		return (NULL);
	while (cylinder->next)
		cylinder = cylinder->next;
	return (cylinder);
}

void	set_cylinder(t_cylinder **cylinder, t_point *pos_vect[2], \
	double diam_height[2], int clr)
{
	t_cylinder	*new;
	t_cylinder	*tmp;

	new = new_cylinder(pos_vect, diam_height, clr);
	if (!*cylinder)
	{
		*cylinder = new;
		return ;
	}
	tmp = get_last_cylinder(*cylinder);
	tmp->next = new;
}
