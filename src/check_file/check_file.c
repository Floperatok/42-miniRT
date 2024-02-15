/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_file.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: drenassi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/15 17:40:45 by drenassi          #+#    #+#             */
/*   Updated: 2024/02/15 21:17:01 by drenassi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

static int	check_extension(char *file)
{
	int		len;
	int		fd;

	fd = open(file, O_RDONLY);
	if (fd == -1)
		return (perror(file), 0);
	close(fd);
	len = ft_strlen(file);
	if (file[len - 1] != 't' || file[len - 2] != 'r' || file[len - 3] != '.')
	{
		print_error("Error: The scene description file must ");
		print_error("have the \".rt\" extension.\n");
		return (0);
	}
	return (1);
}

static int	check_identifier(char *str)
{
	char	*line;

	line = ft_strtrim(str, " ");
	if (line[0] == 'A' && line[1] == ' ')
		return (free(line), 1);
	else if (line[0] == 'C' && line[1] == ' ')
		return (free(line), 1);
	else if (line[0] == 'L' && line[1] == ' ')
		return (free(line), 1);
	else if (line[0] == 's' && line[1] == 'p' && line[2] == ' ')
		return (free(line), 1);
	else if (line[0] == 'p' && line[1] == 'l' && line[2] == ' ')
		return (free(line), 1);
	else if (line[0] == 'c' && line[1] == 'y' && line[2] == ' ')
		return (free(line), 1);
	print_error("Error: Wrong identifier. List of valid identifiers:\n");
	print_error("A for Ambient lightning;\nC for Camera;\nL for Light;\n");
	print_error("sp for Sphere;\npl for Plane;\ncy for Cylinder.\n");
	return (free(line), 0);
}

static int	check_line(char *line)
{
	char	**data;

	if (line[ft_strlen(line) - 1] == '\n')
		line[ft_strlen(line) - 1] = '\0';
	data = ft_split(line, ' ');
	if (!ft_strcmp(data[0], "A") && !check_ambiant_lightning(data))
		return (free_double_array(data), 0);
	return (free_double_array(data), 1);
}

int	check_file(char *file)
{
	char	*line;
	int		fd;

	if (!check_extension(file))
		return (0);
	fd = open(file, O_RDONLY, 666);
	line = get_next_line(fd);
	while (line)
	{
		if ((!is_empty(line) && !check_identifier(line)) || !check_line(line))
			return (close(fd), free(line), 0);
		free(line);
		line = get_next_line(fd);
	}
	return (close(fd), 1);
}
