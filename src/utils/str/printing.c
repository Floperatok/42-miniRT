/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   printing.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nsalles <nsalles@student.42perpignan.fr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/15 17:46:55 by drenassi          #+#    #+#             */
/*   Updated: 2024/03/12 18:19:30 by nsalles          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

void	print_usage(void)
{
	printf("Usage :\n./miniRT your_map.rt "
	"[HardwareMode]\nHardwareMode :\n- 0 = SingleThread\n" 
	"- 1 = MultipleThreads\n- 2 = GPU\nDefault : SingleThread\n");
}

int	print_error(char *msg)
{
	ft_putstr_fd(msg, STDERR_FILENO);
	return (0);
}
