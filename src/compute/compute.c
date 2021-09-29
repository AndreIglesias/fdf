/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   compute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ksoto <ksoto@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/11 20:40:11 by ciglesia          #+#    #+#             */
/*   Updated: 2021/09/27 08:12:06 by ksoto            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

/*
** max_calculator: calculate the max number between 2
*/

int	max_calculator(int a, int b)
{
	if (a > b)
		return (a);
	return (b);
}

/*
** module: apply module to a number
*/

int	module(int a)
{
	if (a < 0)
		a = a * -1;
	return (a);
}

/*
** convert_isometric: reasign the values of x y to a isometric
*/

void	convert_isometric(t_pixel *px, int z, t_fdf *fdf)
{
	if (fdf->view == 3)
	{
		px->x = (px->x - px->y) * cos(0.7);
		px->y = (px->x + px->y) * sin(0.7) - z;
	}
}

/*
** set_color: set color number in the structure
*/

void	set_color(t_fdf *fdf)
{
	long	z;
	long	z1;

	ft_putnbr(fdf->mapy);
	write(1, ",", 2);
	ft_putnbr(fdf->mapx);

	write(1, "B", 1);
	z = fdf->map[(int)fdf->init->y][(int)fdf->init->x].z;

	write(1, "U", 1);

	ft_putnbr(fdf->end->y);
	write(1, ", ", 2);
	ft_putnbr(fdf->end->x);

	z1 = fdf->map[(int)fdf->end->y][(int)fdf->end->x].z;
	write(1, "G\n", 2);
	if (z || z1)
		fdf->color = 0xe80c0c;
	else
		fdf->color = 0xffffff;
}
