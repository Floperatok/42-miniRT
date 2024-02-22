/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   brouillon2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: drenassi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/21 12:51:01 by drenassi          #+#    #+#             */
/*   Updated: 2024/02/22 10:35:40 by drenassi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

#define MAX_RAY_DEPTH 3
#define PRECISION 0.001

typedef struct s_ray
{
	t_point	origin;
	t_point	dir;
	int		depth;
}	t_ray;

// typedef struct s_obj
// {
// 	t_plane			*pl;
// 	t_sphere		*sp;
// 	t_cylinder		*cy;
// 	struct s_obj	*next;
// }	t_obj;

typedef struct s_closest_obj
{
	t_obj	*obj;
	double	distance;
}	t_closest_obj;

typedef struct s_viewport
{
	double	w;
	double	w_ratio;
	double	h;
	double	h_ratio;
}	t_viewport;


t_point	intersection_point(t_ray ray, double distance);

/******************************** OBJECTS LIST ********************************/
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


/******************************** INIT OBJECTS ********************************/
/*
*	Fills all planes in objects list.
*/
static void	init_objs_pl(t_data *data)
{
	t_plane	*pl;

	pl = data->planes;
	while (pl)
	{
		set_objs(&data->objs, pl, NULL, NULL);
		pl = pl->next;
	}
}

/*
*	Fills all spheres in objects list.
*/
static void	init_objs_sp(t_data *data)
{
	t_sphere	*sp;

	sp = data->spheres;
	while (sp)
	{
		set_objs(&data->objs, NULL, sp, NULL);
		sp = sp->next;
	}
}

/*
*	Fills all cylinders in objects list.
*/
static void	init_objs_cy(t_data *data)
{
	t_cylinder	*cy;

	cy = data->cylinders;
	while (cy)
	{
		set_objs(&data->objs, NULL, NULL, cy);
		cy = cy->next;
	}
}

/*
*	Initializes the objects list.
*/
void	init_objs(t_data *data)
{
	data->objs = NULL;
	if (data->planes)
		init_objs_pl(data);
	if (data->spheres)
		init_objs_sp(data);
	if (data->cylinders)
		init_objs_cy(data);
}

/******************************** INTERSECTION ********************************/
/*
*	Returns the minimum solution of the quadratic equation, or min if both
*	values are smaller.
*/
double	quadratic_min(double a, double b, double c, double min)
{
	double	x;
	double	y;
	double	delta;

	delta = b * b - 4 * a * c;
	// printf("delta = %.1f, a = %.1f, b = %.1f, c = %.1f, b^2 = %.1f\n", delta, a, b, c, b * b);
	if (delta < 0)
		return (INFINITY);
	delta = sqrt(delta);
	x = (-b - delta) / (2 * a);
	y = (-b + delta) / (2 * a);
	// printf("x = %f, y = %f\n", x, y);
	if (x < y && x > min)
		return (x);
	else if (y > min)
		return (y);
	else
		return (INFINITY);
}

/*
*	Returns the distance from the ray's origin to the intersection point
*	with a plane.
*/
double	pl_intersection(t_ray ray, t_plane *pl)
{
	double		scalar;
	t_point		ray_to_pl;

	scalar = vector_scalar_product(ray.dir, *pl->normal);
	if (fabs(scalar) < PRECISION)
		return (INFINITY);
	ray_to_pl = soustract_vect(*pl->pos, ray.origin);
	return (vector_scalar_product(*pl->normal, ray_to_pl) / scalar);
}

/*
*	Returns the distance from the ray's origin to the intersection point
*	with a sphere.
*/
double	sp_intersection(t_ray ray, t_sphere *sp)
{
	t_point	ray_to_sp;
	double	a;
	double	b;
	double	c;

	ray_to_sp = soustract_vect(ray.origin, *sp->pos);
	// printf("Intersect: %f %f %f\n", ray_to_sp.x, ray_to_sp.y, ray_to_sp.z);
	a = vector_scalar_product(ray.dir, ray.dir);
	b = 2 * vector_scalar_product(ray_to_sp, ray.dir);
	c = vector_scalar_product(ray_to_sp, ray_to_sp) - sp->radius * sp->radius;
	return (quadratic_min(a, b, c, PRECISION));
}

/*
*	Returns the distance from the ray's origin to the intersection point
*	with an object.
*/
double	obj_intersection(t_ray ray, t_obj *obj)
{
	if (!obj)
		return (INFINITY);
	if (obj->pl)
		return (pl_intersection(ray, obj->pl));
	else if (obj->sp)
		return (sp_intersection(ray, obj->sp));
	// else if (obj->cy)
	// 	return (cy_intersection(ray, obj->cy));
	else
		return (INFINITY);
}

/*
*	Returns the closest object from ray's origin and its distance from it.
*/
t_closest_obj	closest_intersection(t_ray ray, t_obj *objs)
{
	double			distance;
	double			closest_distance;
	t_obj			*obj;
	t_obj			*closest;
	t_closest_obj	res;

	closest = NULL;
	closest_distance = INFINITY;
	obj = objs;
	while (obj)
	{
		distance = obj_intersection(ray, obj);
		if (distance > PRECISION && distance < closest_distance)
		{
			closest_distance = distance;
			closest = obj;
		}
		obj = obj->next;
	}
	res.obj = closest;
	res.distance = closest_distance;
	return (res);
}

/**************************** INTERSECTION NORMALS ****************************/
/*
*	Returns the normal vector resulting from the intersection of a ray
*	and an object, starting from the intersection point.
*/
t_point	get_obj_normal(t_obj *obj, t_point intersection, t_point dir)
{
	t_point	normal;

	if (obj->pl)
	{
		normal = normalize_vect(*obj->pl->normal);
		if (vector_scalar_product(normal, dir) > 0)
		{
			normal = soustract_vect((t_point){0,0,0}, normal);
			*obj->pl->normal = normal;
		}
	}
	if (obj->sp)
		normal = normalize_vect(soustract_vect(intersection, *obj->sp->pos));
	// if (obj->cy)
		
	return (normal);
}


/*********************************** LIGHTS ***********************************/
/*
*	Returns the base color of an object.
*/
t_color	get_obj_color(t_obj *obj)
{
	if (obj->pl)
		return (int_to_rgb(obj->pl->color));
	else if (obj->sp)
		return (int_to_rgb(obj->sp->color));
	else if (obj->cy)
		return (int_to_rgb(obj->cy->color));
	else
		return ((t_color){0, 0, 0, 0});
}

/*
*	Returns the light intensity.
*/
t_point	light_intensity(t_data *data)
{
	t_point			light_color;
	t_point			max_sum;

	light_color.x = int_to_rgb(data->light->color).r;
	light_color.y = int_to_rgb(data->light->color).g;
	light_color.z = int_to_rgb(data->light->color).b;
	max_sum = vect_multiply(light_color, \
		data->light->brightness / int_to_rgb(data->light->color).sum);
	return ((t_point){1 / max_sum.x, 1 / max_sum.y, 1 / max_sum.z});
}

/*
*	Returns the color resulting from a colored light applied
*	on a colored pixel.
*/
t_color	apply_light(t_data *data, t_closest_obj closest)
{
	t_color		obj_color;
	t_color		color;
	t_point		intensity;

	obj_color = get_obj_color(closest.obj);
	intensity = light_intensity(data);
	color.r = obj_color.r * intensity.x;
	color.g = obj_color.g * intensity.y;
	color.b = obj_color.b * intensity.z;
	color.sum = color.r + color.g + color.b;
	protect_colors(&color);
	return (color);
}

/*
*	Returns the direction of the reflected ray.
*/
t_point	reflection_dir(t_point normal, t_point dir)
{
	t_point		reflection;
	double		scalar;

	scalar = vector_scalar_product(dir, normal);
	reflection.x = 2 * scalar * normal.x - dir.x;
	reflection.y = 2 * scalar * normal.y - dir.y;
	reflection.z = 2 * scalar * normal.z - dir.z;
	return (reflection);
}

/********************************* RAYTRACING *********************************/
/*
*	Initialize the primary ray, starting from camera's position in camera's
*	direction.
*/
void	init_ray(t_data *data, t_ray *ray)
{
	ray->origin = *data->camera->pos;
	ray->dir = *data->camera->direction;
	ray->depth = 6;
}

/*
*	Returns the ray intersection point coordinates from the ray's origin.
*/
t_point	intersection_point(t_ray ray, double distance)
{
	t_point	intersection;

	intersection = add_vect(ray.origin, vect_multiply(ray.dir, distance));
	return (intersection);
}

/*
*	Returns the ray's direction and lenght.
*/
t_point	set_ray_dir(t_point base[3], double x, double y, double z)
{
	t_point	new;

	new.x = base[0].x * x + base[1].x * y + base[2].x * z;
	new.y = base[0].y * x + base[1].y * y + base[2].y * z;
	new.z = base[0].z * x + base[1].z * y + base[2].z * z;
	return (new);
}

/*
*	Returns the reflection color of a given color according to a reflect ratio.
*/
static t_color	reflection_color(t_color color, t_color reflective, double ratio)
{
	t_color	res;

	res.r = color.r * (1 - ratio) + reflective.r * ratio;
	res.g = color.g * (1 - ratio) + reflective.g * ratio;
	res.b = color.b * (1 - ratio) + reflective.b * ratio;
	protect_colors(&res);
	res.sum = res.r + res.g + res.b;
	return (res);
}

/*
*	Traces the primary ray. It will stop at the first intersection with
*	an object, change the color of the intersection point, then reflect
*	back in a recursive way.
*/
static t_color	ray_trace(t_data *data, t_ray ray, int depth)
{
	t_closest_obj	closest;
	t_point			closest_normal;
	t_color			color;
	t_color			reflect_color;

	closest = closest_intersection(ray, data->objs);
	if (!closest.obj)
		return ((t_color){0, 0, 0, 0});
	closest_normal = get_obj_normal(closest.obj, \
	intersection_point(ray, closest.distance), ray.dir);
	color = apply_light(data, closest);
	ray.origin = intersection_point(ray, closest.distance);
	ray.dir = soustract_vect((t_point){0, 0, 0}, ray.dir);
	ray.dir = reflection_dir(closest_normal, ray.dir);
	reflect_color = ray_trace(data, ray, depth - 1);
	return (reflection_color(color, reflect_color, 0.1));
}

/*
*	Initializes the viewport in function of the horizontal FOV and the
*	distance from the camera's origin.
*/
t_viewport	init_viewport(double fov, double distance)
{
	t_viewport	vp;
	double	screen_ratio;

	screen_ratio = SCREEN_W / SCREEN_H;
	vp.w = fabs(2 * distance * tan(fov / 2));
	vp.w_ratio = vp.w / SCREEN_W;
	vp.h = vp.w / screen_ratio;
	vp.h_ratio = vp.h / SCREEN_H;
	return (vp);
}

/********************************* DRAW PIXEL *********************************/
/*
*	Draws a pixel in a given color at (x, y) coordinates.
*/
void	draw_pixels(t_image *img, int x, int y, int color)
{
	unsigned int	*pixel;

	pixel = (unsigned int *)(img->addr + (y * img->line_length + \
	x * (img->bits_per_pixel / 8)));
	*pixel = color;
}

/********************************* ROTATIONS **********************************/
/*
*	Returns the cross product of vector v1 by vector v2.
*/
t_point	vector_cross_product(t_point v1, t_point v2)
{
	t_point	res;

	res.x = v2.y * v1.z - v1.y * v2.z;
	res.y = v2.z * v1.x - v1.z * v2.x;
	res.z = v2.x * v1.y - v1.x * v2.y;
	return (res);
}

/*
*	Returns the sinus of the angle formed by two vectors.
*/
double	vector_sin(t_point v1, t_point v2)
{
	return (ft_lenght(vector_cross_product(v1, v2)) \
		/ (ft_lenght(v1) * ft_lenght(v2)));
}

/*
*	Returns the cosinus of the angle formed by two vectors.
*/
double	vector_cos(t_point v1, t_point v2)
{
	return (vector_scalar_product(v1, v2) / (ft_lenght(v1) * ft_lenght(v2)));
}

/*
*	Returns the vector resulting of the rotation of a vector around an axis.
*/
t_point	rotate_vector(t_point vector, t_point axis, double cos, double sin)
{
	t_point	rotated;

	rotated.x = (axis.x * axis.x * (1 - cos) + cos) * vector.x \
		+ (axis.x * axis.y * (1 - cos) - axis.z * sin) * vector.y \
		+ (axis.x * axis.z * (1 - cos) + axis.y * sin) * vector.z;
	rotated.y = (axis.x * axis.y * (1 - cos) + axis.z * sin) * vector.x \
		+ (axis.y * axis.y * (1 - cos) + cos) * vector.y \
		+ (axis.y * axis.z * (1 - cos) - axis.x * sin) * vector.z;
	rotated.z = (axis.x * axis.z * (1 - cos) - axis.y * sin) * vector.x \
		+ (axis.y * axis.z * (1 - cos) + axis.x * sin) * vector.y \
		+ (axis.z * axis.z * (1 - cos) + cos) * vector.z;
	return (rotated);
}

/*
*	Changes a base direction, rotating it around its third vector to
*	match with the given direction.
*/
void	rotate_base(t_point base[3], t_point direction)
{
	t_point		axis;
	double		cos;
	double		sin;

	axis = vector_cross_product(normalize_vect(direction), base[2]);
	cos = vector_cos(normalize_vect(direction), base[2]);
	sin = vector_sin(normalize_vect(direction), base[2]);
	base[0] = rotate_vector(base[0], axis, cos, sin);
	base[1] = rotate_vector(base[1], axis, cos, sin);
	base[2] = rotate_vector(base[2], axis, cos, sin);
}

/********************************* RENDERING **********************************/
/*
*	Draws the 2D rendering of a 3D simulation using a ray-tracing method.
*/
void	rendering(t_data *data, t_image *img)
{
	t_ray		ray;
	t_point		pixel;
	t_color		color;
	t_point		base[3];
	t_viewport	vp;

	color = (t_color){0, 0, 0, 0};
	init_objs(data);
	init_ray(data, &ray);
	base[0] = (t_point){1, 0, 0};
	base[1] = (t_point){0, 1, 0};
	base[2] = (t_point){0, 0, 1};
	rotate_base(base, *data->camera->direction);
	vp = init_viewport(data->camera->fov, 1);
	pixel.x = -SCREEN_W / 2 - 1;
	while (++pixel.x <= SCREEN_W / 2)
	{
		display_loading("Rendering:", -SCREEN_W / 2, pixel.x, SCREEN_W / 100);
		pixel.y = -SCREEN_H / 2 - 1;
		while (++pixel.y <= SCREEN_H / 2)
		{
			ray.dir = set_ray_dir(base, pixel.x * vp.w_ratio, \
				pixel.y * vp.h_ratio, 1);
			color = ray_trace(data, ray, ray.depth);
			draw_pixels(img, SCREEN_W / 2 + pixel.x, SCREEN_H / 2 \
				+ pixel.y, rgb_to_int(color.r, color.g, color.b));
		}
	}
}

