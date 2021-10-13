/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   aux.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ksoto <ksoto@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/13 03:08:17 by ksoto             #+#    #+#             */
/*   Updated: 2021/10/13 03:17:38 by ksoto            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"
#include <stdio.h>

void	continue_exit(t_fdf *fdf)
{
	if (fdf->init)
		free(fdf->init);
	if (fdf->end)
		free(fdf->end);
	if (fdf->l.img)
		mlx_destroy_image(fdf->mlx, fdf->l.img);
	if (fdf->win)
		mlx_destroy_window(fdf->mlx, fdf->win);
	if (fdf->mlx)
	{
		mlx_destroy_display(fdf->mlx);
		free(fdf->mlx);
	}
}

int	exit_win(t_fdf	*fdf)
{
	int	i;

	i = 0;
	free_map();
	if (!fdf)
		exit(0);
	continue_exit(fdf);
	if (fdf->bmp)
	{
		while (i < fdf->res[1])
			free(fdf->bmp[i++]);
		free(fdf->bmp);
	}
	exit(0);
	return (1);
}

void	init_map(t_fdf	*fdf)
{
	fdf->init = malloc(sizeof(t_pixel));
	fdf->end = malloc(sizeof(t_pixel));
	if (!fdf->init || !fdf->end)
		exit_win(fdf);
	fdf->l.img = NULL;
	set_coord(fdf->init, 0, 0);
	set_coord(fdf->end, 0, 0);
	fdf->view = 3;
	fdf->zoom = 100;
	fdf->shift_x = 150;
	fdf->shift_y = 150;
	fdf->zoom = 1;
}

void	handle_shift(int key, t_fdf *fdf)
{
	if (key == 65361)
		fdf->shift_x -= 100;
	if (key == 65363)
		fdf->shift_x += 100;
	if (key == 65364)
		fdf->shift_y += 100;
	if (key == 65362)
		fdf->shift_y -= 100;
}

int	key_win(int key, t_fdf *fdf)
{
	if (key == 0xFF1B)
	{
		exit_win(ft_fdf(NULL));
	}
	if (key == 32)
	{
		if (fdf->view == 3)
			fdf->view = 2;
		else
			fdf->view = 3;
	}
	handle_shift(key, fdf);
	if (key == 65293)
		fdf->zoom += 20;
	if (key == 65506)
		fdf->zoom -= 20;
	plot_map(fdf);
	return (0);
}
