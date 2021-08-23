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

void    set_pixel(t_pixel)

void    bresenham_alg_plot(t_pixel *origin, t_pixel *dest, t_fdf *ft_fdf)
{
    float   diff_x;
    float   diff_y;
    int     max;

    diff_x = dest->x - origin->x;
    diff_y = dest->y - origin->y;
    max = max_calculator(module(diff_x), module(diff_y));
    diff_x /= max;
    diff_y /= max;
    while ((int)(origin->x - dest->x) || (int)(origin->y - dest->y))
    {
        // mlx_pixel_put
        origin->x += diff_x;
        origin->y += diff_y;
    }
}

int     plot_lines(t_fdf *ft_fdf)
{

}