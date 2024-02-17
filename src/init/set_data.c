/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_data.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: drenassi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/17 18:58:35 by drenassi          #+#    #+#             */
/*   Updated: 2024/02/17 20:50:32 by drenassi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

static void	set_line_data(char *line, t_data *data)
{
	char	**datas;

	datas = create_data_array(line);
	if (!ft_strcmp(datas[0], "A"))
		data->a_lights = (ft_atof(datas[1]), format_color(datas[2]));
	if (!ft_strcmp(datas[0], "C"))
		data->cameras = set_camera(str_to_point(datas[1]), \
			str_to_point(datas[2]), ft_atoi(datas[3]));
	if (!ft_strcmp(datas[0], "L") && !check_light(data))
		data->light = set_light(str_to_point(datas[1]), \
			ft_atof(datas[2]), format_color(datas[3]));
	if (!ft_strcmp(datas[0], "pl") && !check_plane(data))
		// data->spheres = 
	// if (!ft_strcmp(datas[0], "sp") && !check_sphere(data))
	// {
		
	// }
	// if (!ft_strcmp(datas[0], "cy") && !check_cylinder(data))
	// {
		
	// }
	return (free_double_array(data), 1);
}

static void	set_all_datas(char *file)
{
	char	*line;
	int		fd;

	fd = open(file, O_RDONLY, 666);
	line = get_next_line(fd);
	while (line)
	{
		
		free(line);
		line = get_next_line(fd);
	}
	return (close(fd), 1);
}

// t_data	*set_data(char *file)
// {
	
// }
