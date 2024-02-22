/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_data.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: drenassi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/18 11:57:48 by drenassi          #+#    #+#             */
/*   Updated: 2024/02/21 17:20:07 by drenassi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

static void	print_separator(void)
{
	printf("|_______________|_______________________________|_______");
	printf("________________|_______________|_______|_______________|\n");
}

static void	print_plane_data(t_plane *planes)
{
	t_plane	*ptr;

	ptr = planes;
	while (ptr)
	{
		printf("|    Plane\t|\t%.1f\t%.1f\t%.1f\t|", ptr->pos->x, \
			ptr->pos->y, ptr->pos->z);
		printf("   %.1f  %.1f  %.1f\t|", ptr->normal->x, \
		ptr->normal->y, ptr->normal->z);
		printf("    #%06x\t|\t|\t\t|\n", ptr->color);
		print_separator();
		ptr = ptr->next;
	}
}

static void	print_sphere_data(t_sphere *spheres)
{
	t_sphere	*ptr;

	ptr = spheres;
	while (ptr)
	{
		printf("|    Sphere\t|\t%.1f\t%.1f\t%.1f\t|\t\t\t|", ptr->pos->x, \
			ptr->pos->y, ptr->pos->z);
		printf("    #%06x\t| %.1f\t|\t\t|\n", ptr->color , ptr->radius * 2);
		print_separator();
		ptr = ptr->next;
	}
}

static void	print_cylinder_data(t_cylinder *cylinders)
{
	t_cylinder	*ptr;

	ptr = cylinders;
	while (ptr)
	{
		printf("|   Cylinder\t|\t%.1f\t%.1f\t%.1f\t|", ptr->pos->x, \
			ptr->pos->y, ptr->pos->z);
		printf("   %.1f  %.1f  %.1f\t|", ptr->vector->x, \
		ptr->vector->y, ptr->vector->z);
		printf("    #%06x\t| %.1f\t|", ptr->color, ptr->radius * 2);
		printf("   H: %.1f\t|\n", ptr->height);
		print_separator();
		ptr = ptr->next;
	}
}

void	print_data(t_data data)
{
	printf(" ________________________________________________________________");
	printf("_______________________________________________\n|      Type\t|\t");
	printf("     Position\t\t|\tDirection\t|     Color\t| Diam.\t|     Other");
	printf("\t|\n|_______________|_______________________________|_");
	printf("______________________|_______________|_______|_______________|\n");
	printf("|  Amb. light.\t|\t\t\t\t|\t\t\t|    #%06x", data.a_light->color);
	printf("\t|\t|   Ratio: %.1f\t|\n", data.a_light->ratio);
	print_separator();
	printf("|    Camera \t|\t%.1f\t%.1f\t%.1f", data.camera->pos->x, \
		data.camera->pos->y, data.camera->pos->z);
	printf("\t|   %.1f  %.1f  %.1f\t|\t\t|\t|", data.camera->direction->x, \
		data.camera->direction->y, data.camera->direction->z);
	printf("    FOV: %d\t|\n", data.camera->fov);
	print_separator();
	printf("|    Light\t|\t%.1f\t%.1f\t%.1f\t|\t\t\t|", data.light->pos->x, \
		data.light->pos->y, data.light->pos->z);
	printf("    #%06x\t|\t| ", data.light->color);
	printf("   Br.: %.1f\t| \n", data.light->brightness);
	print_separator();
	if (data.planes)
		print_plane_data(data.planes);
	if (data.spheres)
		print_sphere_data(data.spheres);
	if (data.cylinders)
		print_cylinder_data(data.cylinders);
}
