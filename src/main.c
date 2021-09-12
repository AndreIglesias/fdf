/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ciglesia <ciglesia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/10 18:32:13 by ciglesia          #+#    #+#             */
/*   Updated: 2021/08/12 01:20:31 by ciglesia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

t_fdf	*ft_fdf(char *name)
{
	static t_fdf	fdf;

	if (name)
		load_map(&fdf, name);
	return (&fdf);
}

int	exit_win(void *p __attribute__((unused)))
{
	exit(0);
	return (1);
}

int	key_win(int key, void *p __attribute__((unused)))
{
	t_fdf	*fdf;

	fdf = ft_fdf(NULL);
	if (key == 0xFF1B)
	{
		exit(0);
	}
	if (key == 0xFF20)
	{
		if (fdf->view == 3)
			fdf->view = 2;
		else
			fdf->view = 3;
	}
	return (0);
}
/*
static void	test()
{
	int		a;
	t_fdf	*fdf = ft_fdf(NULL);

	a = 0x11223344;
	fdf->local_endian = 0;
	if (((unsigned char *)&a)[0] == 0x11)
		fdf->local_endian = 1;
	if (!(fdf->mlx = mlx_init()))
		return ;
	mlx_get_screen_size(fdf->mlx, &fdf->res[0], &fdf->res[1]);
	fdf->res[0] -= 10;
	fdf->res[1] -= 10;
	if (!(fdf->win = mlx_new_window(fdf->mlx, fdf->res[0], fdf->res[1], "wireframe")))
		return ;
	mlx_hook(fdf->win, CROSS_EVENT, CROSS_MASK, exit_win, 0);
	mlx_key_hook(fdf->win, key_win, fdf->mlx);
	ft_plot(fdf->mlx, fdf->win, fdf->res, fdf->local_endian);
	mlx_string_put(fdf->mlx, fdf->win, fdf->res[0] / 2 - 35, fdf->res[1] / 2, 0xFFFFFF, "FDF...");
	mlx_loop(fdf->mlx);
}
*/

static void	init_map(void)
{
	t_fdf	*fdf;

	fdf = ft_fdf(NULL);
	fdf->coord_x = 0;
	fdf->coord_y = 0;
	fdf->side_z = 1;
	fdf->side_x = cos(M_PI / 3) * fdf->side_z;
	fdf->side_y = fdf->side_x * sin(M_PI / 6);
}

static void	kate_test(void)
{
	int		a;
	t_fdf	*fdf;

	fdf = ft_fdf(NULL);
	a = 0x11223344;
	fdf->local_endian = 0;
	if (((unsigned char *)&a)[0] == 0x11)
		fdf->local_endian = 1;
	init_map();
	if (!(fdf->mlx = mlx_init()))
		return ;
	mlx_get_screen_size(fdf->mlx, &fdf->res[0], &fdf->res[1]);
	fdf->res[0] -= 10;
	fdf->res[1] -= 10;
	if (!(fdf->win = mlx_new_window(fdf->mlx, fdf->res[0], fdf->res[1], "wireframe")))
		return ;
	mlx_hook(fdf->win, CROSS_EVENT, CROSS_MASK, exit_win, 0);
	mlx_key_hook(fdf->win, key_win, fdf->mlx);
	mlx_loop_hook(fdf->mlx, render_lines, fdf);
	// ft_plot(fdf->mlx, fdf->win, fdf->res, fdf->local_endian);
	// mlx_string_put(fdf->mlx, fdf->win, fdf->res[0] / 2 - 35, fdf->res[1] / 2, 0xFFFFFF, "FDF...");
	mlx_loop(fdf->mlx);
	// mlx_destroy_window(fdf->mlx, fdf->win);
	// mlx_destroy_display(fdf->mlx);
}

static void	fdf(char *file)
{
	t_fdf	*fdf;

	fdf = ft_fdf(file);
	// test();
	kate_test();
	return;
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
