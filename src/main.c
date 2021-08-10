/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ciglesia <ciglesia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/10 18:32:13 by ciglesia          #+#    #+#             */
/*   Updated: 2021/08/11 01:02:20 by ciglesia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

static void	fdf(char *file __attribute__((unused)))
{
	return ;
}

int	main(int ac, char **av)
{
	if (ac == 2)
		fdf(av[1]);
	else
		ft_putstr_fd("Usage: fdf [FILE]\n", 1);
	return (0);
}
