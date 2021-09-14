/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ciglesia <ciglesia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/11 01:27:49 by ciglesia          #+#    #+#             */
/*   Updated: 2021/09/14 15:50:17 by ciglesia         ###   ########.fr       */
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
	if (!(l.img = mlx_new_image(fdf->mlx, fdf->res[0], fdf->res[1])))
		exit(1);
	l.data = mlx_get_data_addr(l.img, &l.bpp, &l.bpl, &l.endian);
	fill_img(&l, fdf->res[0], fdf->res[1], bmp);
	mlx_put_image_to_window(fdf->mlx, fdf->win, l.img, 0, 0);
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
	int		**bmp;//

	fdf = ft_fdf(NULL);
	diff_x = fdf->end->x - fdf->init->x;
	diff_y = fdf->end->y - fdf->init->y;
	max = max_calculator(module(diff_x), module(diff_y));
	diff_x /= max;
	diff_y /= max;
	bmp = ft_memalloc(sizeof(int *) * fdf->res[1]);//
	if (!bmp)//
		exit(1);//
	int		i = 0;//
	while (i < fdf->res[1])//
	{//
		bmp[i] = ft_memalloc(sizeof(int) * fdf->res[0]);//
		if (!bmp[i])//
			exit(1);//
		i++;//
	}//
	while ((int)(fdf->init->x - fdf->end->x) || \
			(int)(fdf->init->y - fdf->end->y))
	{
		bmp[(int)fdf->init->y][(int)fdf->init->x] = 0xffffff;//
		fdf->init->x += diff_x;
		fdf->init->y += diff_y;
	}
	ft_plot(bmp);
}
