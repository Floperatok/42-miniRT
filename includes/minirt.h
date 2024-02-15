/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minirt.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: drenassi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/15 12:47:05 by nsalles           #+#    #+#             */
/*   Updated: 2024/02/15 21:12:20 by drenassi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINIRT_H
# define MINIRT_H

# include <stdio.h>
# include <math.h>
# include "../libs/libft/includes/libft.h"
# include "../libs/minilibx-linux/mlx.h"

/* UTILS */
int		ft_strcmp(const char *s1, const char *s2);
float	ft_atof(char *str);
int		double_array_len(char **array);
void	free_double_array(char **array);
int		print_error(char *msg);
int		is_empty(char *line);

/* CHECK CONFIG FILE*/
int		check_file(char *file);
int		check_rgb(char *param);
int 	check_ambiant_lightning(char **data);

#endif