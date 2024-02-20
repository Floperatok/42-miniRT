/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   brouillon.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: drenassi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/20 15:03:01 by drenassi          #+#    #+#             */
/*   Updated: 2024/02/20 22:57:01 by drenassi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

static double	farest_plane_distance(t_data *data)
{
	t_plane	*planes;
	double		farest_distance;
	double		distance;

	if (!data->planes)
		return (0.0);
	planes = data->planes;
	farest_distance = 0.0;
	while (planes)
	{
		distance = ft_lenght(soustract_vect(*planes->pos, *data->camera->pos));
		if (distance > farest_distance)
			farest_distance = distance;
		planes = planes->next;
	}
	return (farest_distance);
}

static double	farest_sphere_distance(t_data *data)
{
	t_sphere	*spheres;
	double		farest_distance;
	double		distance;

	if (!data->spheres)
		return (0.0);
	spheres = data->spheres;
	farest_distance = 0.0;
	while (spheres)
	{
		distance = ft_lenght(soustract_vect(*(spheres->pos), *(data->camera->pos)))\
			+ spheres->radius;
		if (distance > farest_distance)
			farest_distance = distance;
		spheres = spheres->next;
	}
	return (farest_distance);
}

static double	farest_cylinder_distance(t_data *data)
{
	t_cylinder	*cylinders;
	double		farest_distance;
	double		distance;

	if (!data->cylinders)
		return (0.0);
	cylinders = data->cylinders;
	farest_distance = 0.0;
	while (cylinders)
	{
		distance = ft_lenght(soustract_vect(*cylinders->pos, *data->camera->pos));
		if (distance > farest_distance)
			farest_distance = distance;
		cylinders = cylinders->next;
	}
	return (farest_distance);
}

double	farest_object_distance(t_data *data)
{
	double	farest_distance;

	farest_distance = fmax(farest_plane_distance(data),
		farest_sphere_distance(data));
	
	return (fmax(farest_distance, farest_cylinder_distance(data)));
}

double	sd_plane(t_point p, t_point normal, double h)
{
	double	res;

	res = vector_scalar_product(p, normal) - h;
	if (res < 0)
		res = 0;
	return (res);
}

double	get_distance_min_plane(t_point p, t_plane plane)
{
	double	res;

	res = vector_scalar_product(soustract_vect(*(plane.pos), p), \
		*(plane.normal)) / ft_lenght(*(plane.normal));
	if (res < 0.0)
		res = -res;
	return (res);
}

int	apply_planes_light(t_plane *plane, t_light *light, double ratio)
{
	t_color	plane_color;
	t_point	vector;
	int		sum;
	t_color	lcolor;
	int		res;

	if (!light)
		return (plane->color);
	lcolor = int_to_rgb(light->color);
	sum = lcolor.r + lcolor.g + lcolor.b;
	vector.x = 3 * lcolor.r * light->brightness * ratio / sum;
	vector.y = 3 * lcolor.g * light->brightness * ratio / sum;
	vector.z = 3 * lcolor.b * light->brightness * ratio / sum;
	plane_color = int_to_rgb(plane->color);
	plane_color.r *= vector.x;
	plane_color.g *= vector.y;
	plane_color.b *= vector.z;
	protect_colors(&plane_color);
	res = rgb_to_int(plane_color.r, \
		plane_color.g, plane_color.b);
	// printf("rgb = %i %i %i\n", plane_color.r, plane_color.g, plane_color.b);
	// printf("vect = %f %f %f\n", vector.x, vector.y, vector.z);
	return (res);
}

void	ray_trace_plane(t_data *data, t_point pixel,
		t_image *img, double farest_obj)
{
	t_point		ray;
	t_point		nray;
	t_plane		*plane;
	double		distance[2];
	double		distance_min;
	double		test;

	plane = data->planes;
	if (data->light)
		distance_min = get_distance_min_plane(*data->light->pos, *plane);
	while (plane)
	{
		ray = set_ray(pixel, *data->camera->direction);
		nray = ray;
		distance[0] = 0.0;
		distance[1] = 0.0;
		while (distance[1] < farest_obj)
		{
			distance[0] = sd_plane(soustract_vect(*plane->pos, ray), *plane->normal, 0.0);
			if (distance[0] <= 0.0)
			{
				test = fmin(1, 1 - 3 * fmax(0, distance_min - ft_lenght(soustract_vect(*plane->pos, ray))) / (distance_min + ft_lenght(soustract_vect(*plane->pos, ray))));
				// test = 1;
				// printf("min = %f, ray = %f, test = %f\n", distance_min, ft_lenght(soustract_vect(*plane->pos, ray)), test);
				pixel_put(img, pixel.x, pixel.y, apply_planes_light(plane, data->light, 1 - test));
			}
			distance[1] += distance[0] + 1.0;
			if (distance[0] > 1.0)
				ray = add_vect(ray, vect_multiply(&nray, distance[0]));
			else
				ray = add_vect(ray, nray);
		}
		plane = plane->next;
	}
}

double	get_distance_min_sphere(t_point p, t_sphere sphere)
{
	double	res;

	res = sqrt((p.x - sphere.pos->x) * (p.x - sphere.pos->x) \
		+ (p.y - sphere.pos->y) * (p.y - sphere.pos->y) \
		+ (p.z - sphere.pos->z) * (p.z - sphere.pos->z)) - sphere.radius;
	return (res);
}

double	get_distance_max_sphere(t_point p, t_sphere sphere)
{
	double	res;
	double	to_center;

	to_center = ft_lenght(soustract_vect(*sphere.pos, p));
	res = sqrt(to_center * to_center + sphere.radius * sphere.radius);
	return (res);
}

int	apply_spheres_light(t_sphere *sphere, t_light *light, double ratio)
{
	t_color	sphere_color;
	t_point	vector;
	int		sum;
	t_color	lcolor;
	int		res;

	if (!light)
		return (sphere->color);
	lcolor = int_to_rgb(light->color);
	sum = lcolor.r + lcolor.g + lcolor.b;
	vector.x = 3 * lcolor.r * light->brightness * ratio / sum;
	vector.y = 3 * lcolor.g * light->brightness * ratio / sum;
	vector.z = 3 * lcolor.b * light->brightness * ratio / sum;
	sphere_color = int_to_rgb(sphere->color);
	sphere_color.r *= vector.x;
	sphere_color.g *= vector.y;
	sphere_color.b *= vector.z;
	protect_colors(&sphere_color);
	res = rgb_to_int(sphere_color.r, \
		sphere_color.g, sphere_color.b);
	return (res);
}

void	ray_trace_sphere(t_data *data, t_point pixel,
		t_image *img, double farest_obj)
{
	t_point		ray;
	t_point		nray;
	t_sphere	*sphere;
	double		distance[2];
	int			printed;
	
	double		min;
	double		max;
	double		test;

	sphere = data->spheres;
	if (data->light)
	{
		min = get_distance_min_sphere(*data->light->pos, *sphere);
		max = get_distance_max_sphere(*data->light->pos, *sphere);
	}
	while (sphere)
	{
		ray = normalize_vect(set_ray(pixel, *data->camera->direction));
		nray = ray;
		distance[0] = 0.0;
		distance[1] = 0.0;
		printed = 0;
		while (distance[1] < farest_obj)
		{
			distance[0] = sd_sphere(soustract_vect(*sphere->pos, ray), \
				sphere->radius);
			if (distance[0] <= 0.0)
			{
				// printf("ray: %f %f %f\n", ray.x, ray.y, ray.z);
				test = 0.2 + (1.0 - 0.2) * (ft_lenght(soustract_vect(ray, *data->light->pos)) - min) / (max - min);
				if (test > 1)
					test = 1;
				else if (test < 0.2)
					test = 0.2;
				printf("min = %.2f, max = %.2f, ray = %f, test = %f\n", min, max, ft_lenght(soustract_vect(ray, *data->light->pos)), test);
				pixel_put(img, pixel.x, pixel.y, apply_spheres_light(sphere, data->light, test));
				if (!printed)
					printed = 1;
			}
			distance[1] += distance[0] + 1.0;
			if (distance[0] > 1.0)
				ray = add_vect(ray, vect_multiply(&nray, distance[0]));
			else
				ray = add_vect(ray, nray);
		}
		sphere = sphere->next;
	}
}

void	raytracing_david(t_data *data, t_image *img)
{
	t_point		pixel;
	double	farest_obj;

	farest_obj = farest_sphere_distance(data);
	pixel.y = -1;
	while (++pixel.y < SCREEN_H)
	{
		display_loading("Rendering:", 0, pixel.y + 1, SCREEN_H / 100);
		pixel.x = -1;
		while (++pixel.x < SCREEN_W)
		{
			if (data->planes)
				ray_trace_plane(data, pixel, img, farest_obj);
			if (data->spheres)
				ray_trace_sphere(data, pixel, img, farest_obj);
		}
	}
}
