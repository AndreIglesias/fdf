/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   compute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ksoto <ksoto@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/11 20:40:11 by ciglesia          #+#    #+#             */
/*   Updated: 2021/10/13 03:50:58 by ksoto            ###   ########.fr       */
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

void	set_color(t_fdf *fdf, int **bmp, int z, int z1)
{
	while (((int)(fdf->init->x - fdf->end->x) || \
			(int)(fdf->init->y - fdf->end->y)) && \
			((int)fdf->init->y > 0) && \
			((int)fdf->init->x > 0) && \
			((int)fdf->init->y < fdf->res[1]) && \
			((int)fdf->init->x < fdf->res[0])
			)
	{
		if (z || z1)
			bmp[(int)fdf->init->y][(int)fdf->init->x] = 0xE80C0C;
		else
			bmp[(int)fdf->init->y][(int)fdf->init->x] = 0xFFFFFF;
		if (fdf->color)
			bmp[(int)fdf->init->y][(int)fdf->init->x] = fdf->color;
		else if (fdf->color1)
			bmp[(int)fdf->init->y][(int)fdf->init->x] = fdf->color1;
		fdf->init->x += fdf->diff_x;
		fdf->init->y += fdf->diff_y;
	}
}

/*
** bresenham_line: bresenham algorithm to plot a line pixel by pixel
** diff_x: distance that x need to advance
** diff_y: distance that y need to advance
*/

void	bresenham_line(t_fdf *fdf, int **bmp)
{
	int		max;
	long	z;
	long	z1;

	z = fdf->map[(int)fdf->init->y][(int)fdf->init->x].z;
	z1 = fdf->map[(int)fdf->end->y][(int)fdf->end->x].z;
	fdf->color = fdf->map[(int)fdf->init->y][(int)fdf->init->x].color;
	fdf->color1 = fdf->map[(int)fdf->init->y][(int)fdf->init->x].color;
	convert_zoom(fdf);
	convert_isometric(fdf->init, z, fdf);
	convert_isometric(fdf->end, z1, fdf);
	convert_shift(fdf);
	fdf->diff_x = fdf->end->x - fdf->init->x;
	fdf->diff_y = fdf->end->y - fdf->init->y;
	max = max_calculator(module(fdf->diff_x), module(fdf->diff_y));
	fdf->diff_x /= max;
	fdf->diff_y /= max;
	set_color(fdf, bmp, z, z1);
}
