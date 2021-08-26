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

void		ft_plot(void *mlx, void *win, int *res, int local_endian)
{
	t_layer	l;

	if (!(l.img = mlx_new_image(mlx, res[0], res[1])))
		exit(1);
	l.data = mlx_get_data_addr(l.img, &l.bpp, &l.bpl, &l.endian);
	fill_img(&l, res[0], res[1], local_endian);
	mlx_put_image_to_window(mlx, win, l.img, 0, 0);
}

/*
** plot pixel
*/

void    set_pixel(t_pixel *pixel, float x, float y)
{
    pixel->x = x;
    pixel->y = y;
}

void    bresenham_alg_plot(t_pixel *origin, t_pixel *dest, t_fdf *fdf)
{
    float   diff_x;
    float   diff_y;
    int     max;
    int     z1;
    int     z2;

    z1 = fdf->map[(int)origin->y][(int)origin->x].z;
    z2 = fdf->map[(int)dest->y][(int)dest->x].z;
    convert_isometric(origin, z1, fdf);
	convert_isometric(dest, z2, fdf);
    diff_x = dest->x - origin->x;
    diff_y = dest->y - origin->y;
    max = max_calculator(module(diff_x), module(diff_y));
    diff_x /= max;
    diff_y /= max;
    while ((int)(origin->x - dest->x) || (int)(origin->y - dest->y))
    {
        mlx_pixel_put(fdf->mlx, fdf->win, origin->x, origin->y, fdf->map[(int)origin->y][(int)origin->x].color);
        origin->x += diff_x;
        origin->y += diff_y;
    }
}


void    render_vertical(t_pixel *p1, t_pixel *p2, int x, int y)
{
    set_pixel(p1, x, y);
    set_pixel(p2, x + 1, y);
}

void    render_horizontal(t_pixel *p1, t_pixel *p2, int x, int y)
{
    set_pixel(p1, x, y);
    set_pixel(p2, x, y + 1);
}

int     render_lines(t_fdf *fdf)
{
    int x;
    int y;

    mlx_clear_window(fdf->mlx, fdf->win);
    y = -1;
    while (++y < fdf->mapy)
    {
        x = -1;
        while (++x < fdf->mapx)
        {
            if ( x < fdf->mapx - 1)
            {
                render_vertical(fdf->init, fdf->end, x, y);
                bresenham_alg_plot(fdf->init, fdf->end, fdf);
            }
            if ( y < fdf->mapy - 1)
            {
                render_horizontal(fdf->init, fdf->end, x, y);
                bresenham_alg_plot(fdf->init, fdf->end, fdf);
            }
        }
    }
    return (0);
}
