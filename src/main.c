/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ksoto <ksoto@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/10 18:32:13 by ciglesia          #+#    #+#             */
/*   Updated: 2021/10/13 03:19:53 by ksoto            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"
#include <stdio.h>

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
	fdf->mlx = mlx_init();
	if (!fdf->mlx)
		return ;
	mlx_get_screen_size(fdf->mlx, &fdf->res[0], &fdf->res[1]);
	fdf->res[0] -= 10;
	fdf->res[1] -= 10;
	fdf->win = mlx_new_window(fdf->mlx, fdf->res[0], \
		fdf->res[1], "wireframe");
	if (!fdf->win)
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
