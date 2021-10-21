/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ksoto <ksoto@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/11 01:27:49 by ciglesia          #+#    #+#             */
/*   Updated: 2021/10/14 12:01:41 by ksoto            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

static void	set_color_ptr(unsigned char *line, t_layer *l, int color, int x)
{
	int				byte;
	int				dec;
	int				opp;
	unsigned char	*ucolor;
	t_fdf			*fdf;

	fdf = ft_fdf(NULL);
	ucolor = (unsigned char *)&color;
	dec = l->bpp / 8;
	opp = dec;
	byte = x * l->bpp / 8;
	while (dec--)
	{
		*(line + byte + dec) = ((ucolor))[3 - dec];
		if (l->endian)
			*(line + byte + dec) = ((ucolor))[opp - 1 - dec];
		if (l->endian == fdf->local_endian)
		{
			*(line + byte + dec) = ((ucolor))[dec];
			if (l->endian)
				*(line + byte + dec) = ((ucolor))[4 - opp + dec];
		}
	}
}

static void	fill_img(t_layer *l, int w, int h, int **bmp)
{
	int				x;
	int				y;
	int				color;
	unsigned char	*ptr;

	y = 0;
	while (y < h)
	{
		ptr = (unsigned char *)l->data + y * l->bpl;
		x = 0;
		while (x < w)
		{
			color = bmp[y][x];
			set_color_ptr(ptr, l, color, x);
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
	l.img = mlx_new_image(fdf->mlx, fdf->res[0], fdf->res[1]);
	if (!l.img)
		exit_win(ft_fdf(NULL));
	l.data = mlx_get_data_addr(l.img, &l.bpp, &l.bpl, &l.endian);
	fill_img(&l, fdf->res[0], fdf->res[1], bmp);
	mlx_put_image_to_window(fdf->mlx, fdf->win, l.img, 0, 0);
	fdf->l = l;
}

/*
** bresenham_loop: bresenham loop
** fdf: fdf project
*/

void	bresenham_loop(t_fdf *fdf)
{
	int	x;
	int	y;

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
	bresenham_loop(fdf);
	ft_plot(fdf->bmp);
}
