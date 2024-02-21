/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raytracing.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nsalles <nsalles@student.42perpignan.fr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/18 02:48:37 by nsalles           #+#    #+#             */
/*   Updated: 2024/02/21 02:43:15 by nsalles          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

static void	setup_camera(t_camera *cam)
{
	cam->plane_distance = 1;
}

static t_viewport_plane	set_viewport_plane(t_camera *cam, t_image *img)
{
	t_viewport_plane plane;

	plane.height = cam->plane_distance * tan(cam->fov * 0.01745329 / 2) * 2;
	plane.width = plane.height * img->aspect_ratio;
	plane.bottom_left = set_vect(-plane.width / 2, -plane.height / 2,\
		cam->plane_distance);
	return (plane);
}

static void	camera_ray(t_camera *cam, t_viewport_plane *plane, t_image *img)
{
	t_point	pixel;
	t_point	viewport_point_local;
	t_point	viewport_point;
	double	tx;
	double	ty;

	pixel.x = -1;
	while (++pixel.x < img->width)
	{
		pixel.y = -1;
		while (++pixel.y < img->height)
		{
			tx = pixel.x / (img->width - 1);
			ty = pixel.y / (img->height - 1);
			viewport_point_local = add_vect(plane->bottom_left,\
				set_vect(plane->width * tx, plane->height * ty, 0));
			viewport_point = *cam->pos;
			viewport_point.x += cam->direction->x * viewport_point_local.x;
			viewport_point.y += cam->direction->y * viewport_point_local.y;
			viewport_point.z += cam->direction->z * viewport_point_local.z;
		}
	}
}

void	render(t_minirt *mem)
{
	t_viewport_plane plane;

	setup_camera(mem->data->camera);
	plane = set_viewport_plane(mem->data->camera, mem->img);
	camera_ray(mem->data->camera, &plane, mem->img);
}