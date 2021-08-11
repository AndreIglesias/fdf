/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ciglesia <ciglesia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/10 18:33:16 by ciglesia          #+#    #+#             */
/*   Updated: 2021/08/11 05:23:09 by ciglesia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FDF_H
# define FDF_H

# include "libft.h"
# include "mlx.h"

# define CROSS_EVENT 33

/*
**	1L << 17
*/

# define CROSS_MASK 0x20000

typedef struct		s_layer
{
	void			*img;
	int				bpp;
	int				bpl;
	int				endian;
	char			*data;
}					t_layer;

void		ft_plot(void *mlx, void *win, int *res, int local_endian);

#endif
