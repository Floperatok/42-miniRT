/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   readfile.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nsalles <nsalles@student.42perpignan.fr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/24 12:53:30 by nsalles           #+#    #+#             */
/*   Updated: 2024/02/24 12:56:46 by nsalles          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

/*
 *	Reads from fd until EOF in encountered. Returns the readed string.
*/
char	*readfile(int fd)
{
	char	*line;
	char	*result;
	char	*tmp;

	result = ft_strdup("");
	line = get_next_line(fd);
	while (line)
	{
		tmp = ft_strjoin(result, line);
		free(line);
		free(result);
		result = tmp;
		line = get_next_line(fd);
	}
	get_next_line(-1);
	return (result);
}
