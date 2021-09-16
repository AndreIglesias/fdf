/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   navigate.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ksoto <ksoto@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/16 17:52:16 by ksoto             #+#    #+#             */
/*   Updated: 2021/09/16 17:53:34 by ksoto            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

/*
** set_coord: assign values to the pixel
*/

void	set_coord(t_pixel *pixel, float x, float y)
{
	pixel->x = x;
	pixel->y = y;
}

/*
** set_horizontal: set coord points of a horizontal line
*/

void	set_horizontal(t_fdf *fdf, int x, int y)
{
	set_coord(fdf->init, x, y);
	set_coord(fdf->end, x, y + 1);
}

/*
** set_vertical: set coord points of a vertical line
*/

void	set_vertical(t_fdf *fdf, int x, int y)
{
	set_coord(fdf->init, x, y);
	set_coord(fdf->end, x + 1, y);
}

/*
** convert_zoom: zoom in & zoom out using keys "enter" & "shift"
*/

void	convert_zoom(t_fdf *fdf)
{
	fdf->init->x *= fdf->zoom;
	fdf->init->y *= fdf->zoom;
	fdf->end->x *= fdf->zoom;
	fdf->end->y *= fdf->zoom;
}

/*
** convert_shift: shift right, left, up & down
*/

void	convert_shift(t_fdf *fdf)
{
	fdf->init->x += fdf->shift_x;
	fdf->init->y += fdf->shift_y;
	fdf->end->x += fdf->shift_x;
	fdf->end->y += fdf->shift_y;
}
