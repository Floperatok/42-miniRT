/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   objects.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nsalles <nsalles@student.42perpignan.fr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/24 12:49:24 by nsalles           #+#    #+#             */
/*   Updated: 2024/02/24 19:25:36 by nsalles          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

void	destroy_objects(t_objects *objs)
{
	destroy_cylinders(objs->cylinders);
	destroy_planes(objs->planes);
	destroy_spheres(objs->spheres);
}

static int	get_number_of_line(char *str)
{
	int	counter;
	int	i;

	i = -1;
	counter = 1;
	while (str[++i])
		if (str[i] == '\n')
			counter++;
	return (counter);
}

static char	***get_data_objects(char *filecontent)
{
	char	***data_objs;
	char	*line;
	int		line_number;
	int		i;
	int		j;

	line_number = get_number_of_line(filecontent);
	data_objs = malloc(sizeof(char **) * (line_number + 1));
	i = 0;
	while (line_number--)
	{
		j = 0;
		while (filecontent[j] && filecontent[j] != '\n')
			j++;
		if (j != 0)
		{
			line = ft_substr(filecontent, 0, j);
			data_objs[i] = create_data_array(line);
			free(line);
			i++;
		}
		filecontent += j + 1;
	}
	data_objs[i] = NULL;
	return (data_objs);
}

int	get_objects(t_objects *objs, char *filename)
{
	int		fd;
	char	*filecontent;
	char	***data_objs;

	fd = open(filename, O_RDONLY);
	if (fd == -1)
		return (perror(""), 0);
	filecontent = readfile(fd);
	data_objs = get_data_objects(filecontent);
	get_alight(data_objs, &objs->a_light);
	get_camera(data_objs, &objs->camera);
	get_light(data_objs, &objs->light);
	objs->number_of_cylinders = get_cylinders(data_objs, &objs->cylinders);
	objs->number_of_planes = get_planes(data_objs, &objs->planes);
	objs->number_of_spheres = get_spheres(data_objs, &objs->spheres);
	free(filecontent);
	free_triple_array(data_objs);
	return (1);
}
