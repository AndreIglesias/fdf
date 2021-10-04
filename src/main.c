/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ksoto <ksoto@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/10 18:32:13 by ciglesia          #+#    #+#             */
/*   Updated: 2021/10/03 23:07:48 by ksoto            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"
#include <stdio.h>

int	exit_win(t_fdf	*fdf)
{
	int	i;

	i = 0;
	free_map();
	if (!fdf)
		exit(0);
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
	if (fdf->bmp)
	{
		while (i < fdf->res[1])
			free(fdf->bmp[i++]);
		free(fdf->bmp);
	}
	exit(0);
	return (1);
}

static void	init_map(t_fdf	*fdf)
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

t_fdf	*ft_fdf(char *name)
{
	static t_fdf	fdf;

	if (name)
	{
		load_map(&fdf, name);
		init_map(&fdf);
	}
	return (&fdf);
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
//	printf("%d\n", key);
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

void	init_bmp(t_fdf *fdf)
{
	int	i;

	fdf->bmp = ft_memalloc(sizeof(int *) * fdf->res[1]);
	if (!fdf->bmp)
		exit_win(ft_fdf(NULL));
	i = 0;
	while (i < fdf->res[1])
	{
		fdf->bmp[i] = ft_memalloc(sizeof(int) * fdf->res[0]);
		if (!fdf->bmp[i])
			exit_win(ft_fdf(NULL));
		i++;
	}
}

static void	draw_map(void)
{
	int		a;
	t_fdf	*fdf;

	fdf = ft_fdf(NULL);
	a = 0x11223344;
	fdf->local_endian = 0;
	if (((unsigned char *)&a)[0] == 0x11)
		fdf->local_endian = 1;
	if (!(fdf->mlx = mlx_init()))
		return ;
	mlx_get_screen_size(fdf->mlx, &fdf->res[0], &fdf->res[1]);
	fdf->res[0] -= 10;
	fdf->res[1] -= 10;
	if (!(fdf->win = mlx_new_window(fdf->mlx, fdf->res[0], \
		fdf->res[1], "wireframe")))
		return ;
	init_bmp(fdf);
	mlx_hook(fdf->win, CROSS_EVENT, CROSS_MASK, exit_win, 0);
	printf("shift = %d\n", fdf->shift_x);
	mlx_key_hook(fdf->win, key_win, fdf);
	mlx_loop(fdf->mlx);
}

static void	fdf(char *file)
{
	t_fdf	*fdf;

	fdf = ft_fdf(file);
	draw_map();
	return ;
}

int	main(int ac, char **av)
{
	if (ac == 2 && is_file(av[1]) == 4)
		fdf(av[1]);
	else if (ac == 2 && is_file(av[1]) != 4)
		ft_putstr_fd("fdf: invalid file\n", 1);
	else
		ft_putstr_fd("Usage: fdf [FILE]\n", 1);
	return (0);
}
