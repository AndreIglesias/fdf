/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ksoto <ksoto@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/10 18:33:16 by ciglesia          #+#    #+#             */
/*   Updated: 2021/10/13 03:50:54 by ksoto            ###   ########.fr       */
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
	t_layer			l;
	int				mapx;
	int				mapy;
	t_x				**map;
	void			*mlx;
	void			*win;
	int				local_endian;
	int				res[2];
	int				view;
	int				color;
	int				color1;
	int				shift_x;
	int				shift_y;
	float			diff_x;
	float			diff_y;
	int				zoom;
	int				**bmp;
	t_pixel			*init;
	t_pixel			*end;
}					t_fdf;

/*
**	Main
*/

t_fdf	*ft_fdf(char *name);
int		exit_win(t_fdf	*fdf);
void	init_map(t_fdf	*fdf);
int		key_win(int key, t_fdf *fdf);

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
void	bresenham_line(t_fdf *fdf, int **bmp);
void	set_coord(t_pixel *pixel, float x, float y);
void	set_horizontal(t_fdf *fdf, int x, int y);
void	set_vertical(t_fdf *fdf, int x, int y);
void	set_color(t_fdf *fdf, int **bmp, int z, int z1);
void	convert_isometric(t_pixel *px, int z, t_fdf *fdf);
int		module(int a);
int		max_calculator(int a, int b);
void	convert_zoom(t_fdf *fdf);
void	convert_shift(t_fdf *fdf);

#endif
