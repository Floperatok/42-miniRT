/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   objects.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: drenassi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/22 10:45:13 by drenassi          #+#    #+#             */
/*   Updated: 2024/02/22 10:45:46 by drenassi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

/*
*	Destroys one object.
*/
static void	destroy_one_obj(t_obj *obj)
{
	if (!obj)
		return ;
	if (obj->pl)
		destroy_plane(&obj->pl);
	if (obj->sp)
		destroy_sphere(&obj->sp);
	if (obj->cy)
		destroy_cylinder(&obj->cy);
	free(obj);
}

/*
*	Destroy all objects in objects list.
*/
void	destroy_objs(t_obj **obj)
{
	t_obj	*tmp;

	if (!obj)
		return ;
	tmp = *obj;
	while (*obj)
	{
		tmp = (*obj)->next;
		destroy_one_obj(*obj);
		*obj = tmp;
	}
	obj = NULL;
}

/*
*	Creates a new object.
*/
static t_obj	*new_obj(t_plane *pl, t_sphere *sp, t_cylinder *cy)
{
	t_obj	*obj;

	obj = ft_calloc(1, sizeof(t_obj));
	if (!obj)
	{
		print_error("Fatal error: obj struct initialization: ");
		print_error("Out of memory\n");
		return (NULL);
	}
	obj->pl = pl;
	obj->sp = sp;
	obj->cy = cy;
	obj->next = NULL;
	return (obj);
}

/*
*	Returns the last object of the objects list.
*/
static t_obj	*get_last_obj(t_obj *obj)
{
	if (!obj)
		return (NULL);
	while (obj->next)
		obj = obj->next;
	return (obj);
}

/*
*	Creates and adds an object at the end of the objects list.
*/
void	set_objs(t_obj **objs, t_plane *pl, t_sphere *sp, t_cylinder *cy)
{
	t_obj	*new;
	t_obj	*tmp;

	new = new_obj(pl, sp, cy);
	if (!*objs)
	{
		*objs = new;
		return ;
	}
	tmp = get_last_obj(*objs);
	tmp->next = new;
}
