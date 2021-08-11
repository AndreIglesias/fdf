/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ciglesia <ciglesia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/10 18:32:13 by ciglesia          #+#    #+#             */
/*   Updated: 2021/08/11 05:23:25 by ciglesia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

int		exit_win(void *p __attribute__((unused)))
{
	exit(0);
	return (1);
}

int		key_win(int key, void *p __attribute__((unused)))
{
	if (key == 0xFF1B)
	{
		exit(0);
	}
	return (0);
}

static void	test()
{
	int		a;
	void	*mlx;
	void	*win;
	int		res[2];
	int		local_endian;

	a = 0x11223344;
	local_endian = 0;
	if (((unsigned char *)&a)[0] == 0x11)
		local_endian = 1;
	if (!(mlx = mlx_init()))
		return ;
	mlx_get_screen_size(mlx, &res[0], &res[1]);
	res[0] -= 10;
	res[1] -= 10;
	if (!(win = mlx_new_window(mlx, res[0], res[1], "wireframe")))
		return ;
	mlx_string_put(mlx, win, res[0] / 2 - 35, res[1] / 2, 0xFFFFFF, "FDF...");
	mlx_hook(win, CROSS_EVENT, CROSS_MASK, exit_win, 0);
	mlx_key_hook(win, key_win, mlx);
	ft_plot(mlx, win, res, local_endian);
	mlx_loop(mlx);
}

static void	fdf(char *file __attribute__((unused)))
{
	test();
	return ;
}

int	main(int ac, char **av)
{
	if (ac == 2)
		fdf(av[1]);
	else
		ft_putstr_fd("Usage: fdf [FILE]\n", 1);
	return (0);
}
