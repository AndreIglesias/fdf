/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ciglesia <ciglesia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/11 01:27:49 by ciglesia          #+#    #+#             */
/*   Updated: 2021/08/21 23:02:42 by ciglesia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

static void	set_color_ptr(unsigned char *line, t_layer *l, int color, int x, int local_endian)
{
	int				byte;
	int				dec;
	int				opp;
	unsigned char	*ucolor;

	ucolor = (unsigned char *)&color;
	dec = l->bpp / 8;
	opp = dec;
	byte = x * l->bpp / 8;
	while (dec--)
	{
		if (l->endian == local_endian)
		{
			if (l->endian)
				*(line + byte + dec) = ((ucolor))[4 - opp + dec];
			else
				*(line + byte + dec) = ((ucolor))[dec];
		}
		else
		{
			if (l->endian)
				*(line + byte + dec) = ((ucolor))[opp - 1 - dec];
			else
				*(line + byte + dec) = ((ucolor))[3 - dec];
		}
	}
}

static void	fill_img(t_layer *l, int w, int h, int local_endian)
{
	int				x;
	int				y;
	int				color;
	unsigned char	*ptr;
	unsigned char	red = 0x0;
	unsigned char	green = 0x0;
	unsigned char	blue = 0x0;
	int				before = h;

	y = 0;
	while (y < h)
	{
		ptr = (unsigned char *)l->data + y * l->bpl;
		x = 0;
		if (before != 255 * y / h)
		{
			red += 0x1;
			green += 0x1;
			blue += 0x1;
			before = 255 * y / h;
		}
		while (x < w)
		{
			color = ft_rgbtoi(red, green, blue);
			set_color_ptr(ptr, l, color, x, local_endian);
			x++;
		}
		y++;
	}
}

void	ft_plot(void *mlx, void *win, int *res, int local_endian)
{
	t_layer	l;

	if (!(l.img = mlx_new_image(mlx, res[0], res[1])))
		exit(1);
	l.data = mlx_get_data_addr(l.img, &l.bpp, &l.bpl, &l.endian);
	fill_img(&l, res[0], res[1], local_endian);
	mlx_put_image_to_window(mlx, win, l.img, 0, 0);
}

/*
** set pixel: assign values to the pixel
*/

void	set_pixel(t_pixel *pixel, float x, float y)
{
	pixel->x = x;
	pixel->y = y;
}

/*
** bresenham_line: bresenham algorithm to plot a line pixel by pixel
** diff_x: distance that x need to advance
** diff_y: distance that y need to advance
*/

void	bresenham_line(void)
{
	float	diff_x;
	float	diff_y;
	int		max;
	t_fdf	*fdf;

	fdf = ft_fdf(NULL);
	diff_x = fdf->end->x - fdf->init->x;
	diff_y = fdf->end->y - fdf->init->y;
	max = max_calculator(module(diff_x), module(diff_y));
	diff_x /= max;
	diff_y /= max;
	while ((int)(fdf->init->x - fdf->end->x) || \
			(int)(fdf->init->y - fdf->end->y))
	{
		mlx_pixel_put(fdf->mlx, fdf->win, fdf->init->x, fdf->init->y, 0xffffff);
		fdf->init->x += diff_x;
		fdf->init->y += diff_y;
	}
}
