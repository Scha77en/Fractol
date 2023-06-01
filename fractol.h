/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fractol.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aouhbi <aouhbi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/27 22:37:28 by aouhbi            #+#    #+#             */
/*   Updated: 2023/06/01 16:59:57 by aouhbi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FRACTOL_H
# define FRACTOL_H

# include "mlx.h"
# include <math.h>
# include <stdlib.h>
# include <unistd.h>
# include <string.h>
# include <stdio.h>
# include <fcntl.h>

# define WIDTH 800
# define HEIGHT 600
# define ZOOM_FACTOR 1.1
# define MAX_ITER 100
# define COLOR_OFFSET 20

typedef struct s_complex
{
	double	r;
	double	i;
}	t_complex;

typedef struct s_fractal
{
	t_complex	c;
	void		*mlx;
	void		*win;
	void		*img;
	char		*data_addr;
	int			bpp;
	int			size_line;
	int			endian;
	double		zoom;
	double		offset_x;
	double		offset_y;
	char		*fractal_name;
	int			value;
}	t_fractal;

int		handle_key_press(int keycode, t_fractal *fractal);
int		handle_window_close(t_fractal *fractal);
int		handle_arrow_keys(int keycode, t_fractal *fractal);
int		handle_mouse_wheel(int button, int x, int y, t_fractal *fractal);
int		handle_mouse_movement(int x, int y, t_fractal *fractal);
int		mandelbrot_iter(t_complex c, t_complex z);
int		julia_iter(t_complex z, t_complex c);
int		burning_ship(t_complex c, t_complex z);
int		get_color(int n);
int		ft_strcmp(char *s1, char *s2);
void	draw_fractal(t_fractal *fractal);
void	handle_errors(int argc, char **argv);
void	proper_exit(int v);
void	set_mlx(t_fractal fractal);
int		offsets_and_fractals(t_fractal *fractal, int x, int y);
#endif