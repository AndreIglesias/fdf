/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ciglesia <ciglesia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/21 22:35:32 by ciglesia          #+#    #+#             */
/*   Updated: 2021/08/21 23:06:44 by ciglesia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

t_x	**wireframe(int	mx, int my, char *name)
{
	char	*line;
	int		fd;

	(void)mx;
	(void)my;
	fd = open(name, O_RDONLY);
	if (fd < 0)
		exit(1);
	line = NULL;
	while (get_next_line(fd, &line) > 0)
	{
		if (!1)
		{
			get_next_line(-1, &line);
			free(line);
			//free_everything
			close(fd);
			return (NULL);
		}
		free(line);
	}
	free(line);
	close(fd);
	return (NULL);
}
