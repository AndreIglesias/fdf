/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ksoto <ksoto@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/10 18:33:16 by ciglesia          #+#    #+#             */
/*   Updated: 2021/09/29 04:27:43 by ksoto            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FDF_H
# define FDF_H

# include "libft.h"
# include "mlx.h"
# include <fcntl.h>
# include <math.h>

# define CROSS_EVENT 33
# define CROSS_MASK 0x20000

typedef struct s_pixel
{
	float			x;
	float			y;
}					t_pixel;

typedef struct s_layer
{
	void			*img;
	int				bpp;
	int				bpl;
	int				endian;
	char			*data;
}					t_layer;

typedef struct s_x
{
	long			z;
	int				color;
}					t_x;

typedef struct s_fdf
{
	int				mapx;
	int				mapy;
	t_x				**map;
	void			*mlx;
	void			*win;
	int				local_endian;
	int				res[2];
	int				view;
	int				color;
	int				shift_x;
	int				shift_y;
	int				zoom;
	t_pixel			*init;
	t_pixel			*end;
}					t_fdf;

/*
**	Main
*/

t_fdf	*ft_fdf(char *name);

/*
**	Display
*/

void	ft_plot(int **bmp);
void	plot_map(t_fdf *fdf);
// int		render_lines(t_fdf *ft_fdf);

/*
**	Analyze
*/

void	wireframe(char *name);
void	load_map(t_fdf *fdf, char *name);
void	free_map(void);

/*
** Compute
*/
void	set_coord(t_pixel *pixel, float x, float y);
void	set_horizontal(t_fdf *fdf, int x, int y);
void	set_vertical(t_fdf *fdf, int x, int y);
void	set_color(t_fdf *fdf);
void	convert_isometric(t_pixel *px, int z, t_fdf *fdf);
int		module(int a);
int		max_calculator(int a, int b);
void	convert_zoom(t_fdf *fdf);
void	convert_shift(t_fdf *fdf);

#endif
