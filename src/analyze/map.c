/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ksoto <ksoto@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/21 22:35:32 by ciglesia          #+#    #+#             */
/*   Updated: 2021/10/08 04:20:05 by ksoto            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"
#include <stdio.h>

void	ft_extract_color(t_fdf *fdf, char *str, int y, int x)
{
	int	i;
	int	j;
	char	tmp[10];

	i = 0;
	while (str[i])
	{
		if (str[i] == ',')
		{
			j = 0;
			while (j < 10 || str[i])
			{
				tmp[j] = str[i];
				j++;
				i++;
			}
			fdf->map[y][x].color = ft_atoi(tmp); //pasar a base 10 y atoi
		}
		i++;
	}
}

static int	extract_line(t_fdf *fdf, char *line, int y)
{
	char	**tab;
	int		i;

	tab = ft_strsplit(line, ' ');
	i = 0;
	while (i < fdf->mapx)
	{
		// printf("%s ", tab[i]);
		ft_extract_color(fdf, tab[i], y, i);
		fdf->map[y][i].z = ft_atoi(tab[i]);
		// printf("%i ", fdf->map[y][i].color);
		free(tab[i]);
		i++;
	}
	printf("\n");
	free(tab);
	return (1);
}

void	free_map(void)
{
	int		i;
	t_fdf	*fdf;

	fdf = ft_fdf(NULL);
	i = 0;
	while (i < fdf->mapy)
	{
		if (fdf->map[i])
			free(fdf->map[i++]);
	}
	free(fdf->map);
}

static void	extract_lines(t_fdf *fdf, char *line, int fd)
{
	int	y;

	y = 0;
	while (get_next_line(fd, &line) > 0)
	{
		if (!extract_line(fdf, line, y))
		{
			get_next_line(-1, &line);
			free(line);
			free_map();
			close(fd);
			exit(1);
		}
		free(line);
		y++;
	}
	free(line);
	close(fd);
}

void	wireframe(char *name)
{
	int		fd;
	int		size;
	t_fdf	*fdf;

	fdf = ft_fdf(NULL);
	fd = open(name, O_RDONLY);
	if (fd < 0)
		exit(1);
	fdf->map = ft_memalloc(sizeof(t_x *) * (fdf->mapy + 1));
	size = 0;
	while (size < fdf->mapy)
	{
		fdf->map[size++] = ft_memalloc(sizeof(t_x) * (fdf->mapx + 1));
		if (!fdf->map[size - 1])
		{
			free_map();
			exit(1);
		}
	}
	if (!fdf->map)
		exit(1);
	extract_lines(fdf, NULL, fd);
}
