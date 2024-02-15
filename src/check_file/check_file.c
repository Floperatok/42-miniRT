/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_file.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: drenassi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/15 17:40:45 by drenassi          #+#    #+#             */
/*   Updated: 2024/02/15 19:31:40 by drenassi         ###   ########.fr       */
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

static int	check_identifier(char *line)
{
	if (line[0] == 'A')
		return (1);
	else if (line[0] == 'C')
		return (1);
	else if (line[0] == 'L')
		return (1);
	else if (line[0] == 's' && line[1] == 'p')
		return (1);
	else if (line[0] == 'p' && line[1] == 'l')
		return (1);
	else if (line[0] == 'c' && line[1] == 'y')
		return (1);
	print_error("Error: Wrong identifier. List of valid identifiers:\n");
	print_error("A for Ambient lightning;\n");
	print_error("C for Camera;\n");
	print_error("L for Light;\n");
	print_error("sp for Sphere;\n");
	print_error("pl for Plane;\n");
	print_error("cy for Cylinder.\n");
	return (0);
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
		if (line[0] != '\n' && !check_identifier(line))
			return (close(fd), get_next_line(-1), free(line), 0);
		if (line[0] == 'A' && !check_ambiant_lightning(line))
			return (close(fd), get_next_line(-1), free(line), 0);
		free(line);
		line = get_next_line(fd);
	}
	return (close(fd), get_next_line(-1), 1);
}
