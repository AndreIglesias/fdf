/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   analyze.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ciglesia <ciglesia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/11 20:39:56 by ciglesia          #+#    #+#             */
/*   Updated: 2021/08/22 01:33:40 by ciglesia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

static int	x_axis(char *line)
{
	int	c;
	int	i;

	c = 0;
	i = 0;
	while (line[i])
	{
		while (line[i] && line[i] == ' ')
			i++;
		if (line[i] && line[i] != ' ')
			c++;
		while (line[i] && line[i] != ' ')
			i++;
	}
	return (c);
}

static int	hex_color(char *line, int *i)
{
	int	hex;

	hex = 6;
	if (ft_strncmp(&line[(*i) + 1], "0x", 2))
		return (0);
	*i += 3;
	while (--hex >= 0 && ft_strchr("0123456789ABCDEFabcdef", line[*i]))
		(*i)++;
	if ((hex + 1) % 2 != 0)
		return (0);
	return (1);
}

static int	consistent_coords(char *line)
{
	int	i;

	i = 0;
	while (line[i])
	{
		while (line[i] && line[i] == ' ')
			i++;
		i += (line[i] == '-');
		while ('0' <= line[i] && line[i] <= '9')
			i++;
		if (line[i] == ',')
		{
			if (!hex_color(line, &i))
				return (0);
		}
		if (line[i] && line[i] != ' ')
		{
			ft_putstr_fd(&line[i], 1);
			return (0);
		}
	}
	return (1);
}

static int	consistent_map(t_fdf *fdf, char *name, char *line)
{
	int		fd;

	fd = open(name, O_RDONLY);
	if (fd < 0)
		exit(1);
	fdf->mapx = -1;
	fdf->mapy = 0;
	while (get_next_line(fd, &line) > 0)
	{
		if (fdf->mapx == -1)
			fdf->mapx = x_axis(line);
		if (!consistent_coords(line) || fdf->mapx != x_axis(line))
		{
			get_next_line(-1, &line);
			free(line);
			close(fd);
			return (0);
		}
		free(line);
		fdf->mapy++;
	}
	free(line);
	close(fd);
	return (1);
}

void	load_map(t_fdf *fdf, char *name)
{
	if (!consistent_map(fdf, name, NULL))
	{
		ft_putstr_fd("fdf: error: inconsistent line: ", 2);
		ft_putnbr_fd(fdf->mapy + 1, 2);
		ft_putstr_fd("\n", 2);
		exit(0);
	}
	wireframe(name);
}
