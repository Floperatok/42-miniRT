/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minirt.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: drenassi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/15 12:47:05 by nsalles           #+#    #+#             */
/*   Updated: 2024/02/15 19:08:40 by drenassi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINIRT_H
# define MINIRT_H

# include <stdio.h>
# include "../libs/libft/includes/libft.h"
# include "../libs/minilibx-linux/mlx.h"

/* UTILS */
int	print_error(char *msg);

/* CHECK CONFIG FILE*/
int	check_file(char *file);
int check_ambiant_lightning(char *line);

#endif