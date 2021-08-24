/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   compute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ciglesia <ciglesia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/11 20:40:11 by ciglesia          #+#    #+#             */
/*   Updated: 2021/08/11 20:40:12 by ciglesia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

int     max_calculator(int a, int b)
{
    if (a > b)
        return (a);
    return (b);
}

int     module(int a)
{
    if (a < 0)
        a = a * -1;
    return (a);
}

void    set_pixel(t_pixel *pixel, float x, float y)
{
    pixel->x = x;
    pixel->y = y;
}

void    bresenham_alg_plot(t_pixel *origin, t_pixel *dest, t_fdf *ft_fdf)
{
    float   diff_x;
    float   diff_y;
    int     max;
    int     z1;
    int     z2;

    z1 = fdf->map[origin->y][origin->x].z
    z2 = fdf->map[dest->y][dest->x].z
    // isometric
    diff_x = dest->x - origin->x;
    diff_y = dest->y - origin->y;
    max = max_calculator(module(diff_x), module(diff_y));
    diff_x /= max;
    diff_y /= max;
    while ((int)(origin->x - dest->x) || (int)(origin->y - dest->y))
    {
        mlx_pixel_put(fdf->mlx, fdf->win, origin->x, origin->y, fdf->map[origin->y][origin->x].color)
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

int     render_lines(t_fdf *ft_fdf)
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
                render_vertical(fdf->init, fdf->end, x, y)
                bresenham_alg_plot(fdf->init, fdf->end, fdf);
            }
            if ( y < fdf->mapy - 1)
            {
                render_horizontal(fdf->init, fdf->end, x, y)
                bresenham_alg_plot(fdf->init, fdf->end, fdf);
            }
        }
    }
    return (0);
}