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

void    convert_isometric(t_pixel *px, int z, t_fdf *fdf)
{
    if (fdf->view == 3)
    {
        px->x = (px->x - px->y)*cos(0.7);
        px->y = (px->x + px->y)*sin(0.7) - z;
    }
}

/*
void    compute_horizontal(t_fdf *fdf, int x, int y)
{
    int delta_x;
    int delta_y;

    delta_x = x - fdf->mapx / 2;
    delta_y = x - fdf->mapy / 2;
    fdf->y0 = fdf->side_y;
}
*/
