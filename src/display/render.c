/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ksoto <ksoto@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/11 01:27:49 by ciglesia          #+#    #+#             */
/*   Updated: 2021/10/05 15:37:30 by ksoto            ###   ########.fr       */
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

static void	fill_img(t_layer *l, int w, int h, int **bmp)
{
	int				x;
	int				y;
	int				color;
	unsigned char	*ptr;
	t_fdf			*fdf;

	fdf = ft_fdf(NULL);
	y = 0;
	while (y < h)
	{
		ptr = (unsigned char *)l->data + y * l->bpl;
		x = 0;
		while (x < w)
		{
			color = bmp[y][x];
			set_color_ptr(ptr, l, color, x, fdf->local_endian);
			x++;
		}
		y++;
	}
}

void	ft_plot(int **bmp)
{
	t_layer	l;
	t_fdf	*fdf;

	fdf = ft_fdf(NULL);
	if (fdf->l.img)
		mlx_destroy_image(fdf->mlx, fdf->l.img);
	if (!(l.img = mlx_new_image(fdf->mlx, fdf->res[0], fdf->res[1])))
		exit_win(ft_fdf(NULL));
	l.data = mlx_get_data_addr(l.img, &l.bpp, &l.bpl, &l.endian);
	fill_img(&l, fdf->res[0], fdf->res[1], bmp);
	mlx_put_image_to_window(fdf->mlx, fdf->win, l.img, 0, 0);
	fdf->l = l;
}

/*
** bresenham_line: bresenham algorithm to plot a line pixel by pixel
** diff_x: distance that x need to advance
** diff_y: distance that y need to advance
*/

void	bresenham_line(t_fdf *fdf, int **bmp)
{
	float	diff_x;
	float	diff_y;
	int		max;
	long	z;
	long	z1;

	z = fdf->map[(int)fdf->init->y][(int)fdf->init->x].z;
	z1 = fdf->map[(int)fdf->end->y][(int)fdf->end->x].z;
	convert_zoom(fdf);
	convert_isometric(fdf->init, z, fdf);
	convert_isometric(fdf->end, z1, fdf);
	convert_shift(fdf);
	diff_x = fdf->end->x - fdf->init->x;
	diff_y = fdf->end->y - fdf->init->y;
	max = max_calculator(module(diff_x), module(diff_y));
	diff_x /= max;
	diff_y /= max;
	while (((int)(fdf->init->x - fdf->end->x) || \
			(int)(fdf->init->y - fdf->end->y)) && \
			((int)fdf->init->y > 0) && \
			((int)fdf->init->x > 0) && \
			((int)fdf->init->y < fdf->res[1]) && \
			((int)fdf->init->x < fdf->res[0])
			)
	{
		if (z || z1)
			bmp[(int)fdf->init->y][(int)fdf->init->x] = 0xFFFFFF;
		else
			bmp[(int)fdf->init->y][(int)fdf->init->x] = 0x00FF00;
		fdf->init->x += diff_x;
		fdf->init->y += diff_y;
	}
}

/*
** plot_map: plot map
** fdf: fdf project
*/

void	plot_map(t_fdf *fdf)
{
	int	x;
	int	y;

	y = -1;
	while (++y < fdf->res[1])
	{
		x = -1;
		while (++x < fdf->res[0])
			fdf->bmp[y][x] = 0;
	}
	mlx_clear_window(fdf->mlx, fdf->win);
	y = -1;
	while (++y < fdf->mapy)
	{
		x = -1;
		while (++x < fdf->mapx)
		{
			if (x < fdf->mapx - 1)
			{
				set_vertical(fdf, x, y);
				bresenham_line(fdf, fdf->bmp);
			}
			if (y < fdf->mapy - 1)
			{
				set_horizontal(fdf, x, y);
				bresenham_line(fdf, fdf->bmp);
			}
		}
	}
	ft_plot(fdf->bmp);
}
