/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   objects.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nsalles <nsalles@student.42perpignan.fr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/24 12:49:24 by nsalles           #+#    #+#             */
/*   Updated: 2024/03/27 20:39:19 by nsalles          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

void	destroy_objects(t_objects *objs)
{
	destroy_alight(objs->alight);
	destroy_camera(objs->camera);
	destroy_lights(objs->lights);
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

// for debuging
void	print_data_objs(char ***data_objs)
{
	int	i;
	int	j;

	i = -1;
	while (data_objs[++i])
	{
		j = -1;
		printf("{");
		while (data_objs[i][++j])
			printf("[%s] ", data_objs[i][j]);
		printf("}\n");
	}
}

int	get_objects(t_objects *objs, char *filename)
{
	int		fd;
	char	*filecontent;
	char	***data_objs;
	int		num_objects;

	fd = open(filename, O_RDONLY);
	if (fd == -1)
		return (perror(""), 0);
	filecontent = readfile(fd);
	data_objs = get_data_objects(filecontent);
	num_objects = 0;
	while (data_objs[num_objects])
		num_objects++;
	objs->alight = get_alight(data_objs);
	objs->camera = get_camera(data_objs);
	objs->lights = get_lights(data_objs, num_objects);
	objs->cylinders = get_cylinders(data_objs, num_objects);
	objs->planes = get_planes(data_objs, num_objects);
	objs->spheres = get_spheres(data_objs, num_objects);
	free(filecontent);
	free_triple_array(data_objs);
	return (1);
}
