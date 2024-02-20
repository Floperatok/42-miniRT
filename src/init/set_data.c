/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_data.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: drenassi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/17 18:58:35 by drenassi          #+#    #+#             */
/*   Updated: 2024/02/20 14:04:30 by drenassi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

void	destroy_data(t_data *data)
{
	destroy_alight(data->a_light);
	destroy_camera(data->camera);
	destroy_light(data->light);
	destroy_plane(&data->planes);
	destroy_sphere(&data->spheres);
	destroy_cylinder(&data->cylinders);
	free(data);
}

static void	set_line_data2(t_data *data, char **datas)
{
	t_point	*pos_vect[2];
	double	rad_height[2];

	if (!ft_strcmp(datas[0], "pl"))
		set_plane(&(data->planes), str_to_point(datas[1]), \
			str_to_point(datas[2]), format_color(datas[3]));
	if (!ft_strcmp(datas[0], "sp"))
		set_sphere(&(data->spheres), str_to_point(datas[1]), \
			ft_atod(datas[2]) / 2, format_color(datas[3]));
	if (!ft_strcmp(datas[0], "cy"))
	{
		pos_vect[0] = str_to_point(datas[1]);
		pos_vect[1] = str_to_point(datas[2]);
		rad_height[0] = ft_atod(datas[3]) / 2;
		rad_height[1] = ft_atod(datas[4]);
		set_cylinder(&(data->cylinders), pos_vect, rad_height, \
			format_color(datas[5]));
	}
}

static void	set_line_data(char *line, t_data *data)
{
	char	**datas;

	datas = create_data_array(line);
	if (!datas)
		return ;
	if (!ft_strcmp(datas[0], "A"))
		data->a_light = set_alight(ft_atod(datas[1]), \
			format_color(datas[2]));
	if (!ft_strcmp(datas[0], "C"))
		data->camera = set_camera(str_to_point(datas[1]), \
			str_to_point(datas[2]), ft_atoi(datas[3]));
	if (!ft_strcmp(datas[0], "L"))
		data->light = set_light(str_to_point(datas[1]), \
			ft_atod(datas[2]), format_color(datas[3]));
	set_line_data2(data, datas);
	free_double_array(datas);
}

t_data	*set_data(char *file)
{
	char	*line;
	int		fd;
	t_data	*data;

	data = ft_calloc(1, sizeof(t_data));
	fd = open(file, O_RDONLY, 666);
	line = get_next_line(fd);
	while (line)
	{
		set_line_data(line, data);
		free(line);
		line = get_next_line(fd);
	}
	return (close(fd), data);
}
