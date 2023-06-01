/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aouhbi <aouhbi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/27 22:33:53 by aouhbi            #+#    #+#             */
/*   Updated: 2023/06/01 17:00:49 by aouhbi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

int	get_color(int n)
{
	int	red;
	int	green;
	int	blue;

	red = sin(0.3 * n + 7) * 127 + 128;
	green = sin(0.4 * n + 4) * 127 + 128;
	blue = sin(0.3 * n + 4) * 127 + 128;
	return ((red << 16) + (green << 8) + blue);
}

void	draw_fractal(t_fractal *fractal)
{
	int	x;
	int	y;
	int	i;
	int	iter;
	int	color;

	y = 0;
	i = 0;
	while (y < HEIGHT)
	{
		x = 0;
		while (x < WIDTH)
		{
			iter = offsets_and_fractals(fractal, x, y);
			color = get_color(iter + COLOR_OFFSET);
			fractal->data_addr[(x * fractal->bpp / 8)
				+ (y * fractal->size_line)] = color & 0xFF;
			fractal->data_addr[(x * fractal->bpp / 8)
				+ (y * fractal->size_line) + 1] = (color >> 8) & 0xFF;
			fractal->data_addr[(x * fractal->bpp / 8)
				+ (y * fractal->size_line) + 2] = (color >> 16) & 0xFF;
			x++;
		}
		y++;
	}
}

int	offsets_and_fractals(t_fractal *fractal, int x, int y)
{
	t_complex	c;
	t_complex	z;
	int			iter;

	c.r = (x - WIDTH / 2) / (0.5 * fractal->zoom * WIDTH) + fractal->offset_x;
	c.i = (y - HEIGHT / 2) / (0.5 * fractal->zoom * HEIGHT) + fractal->offset_y;
	z.r = 0;
	z.i = 0;
	if (ft_strcmp(fractal->fractal_name, "Mandelbrot") == 0)
		iter = mandelbrot_iter(c, z);
	if (ft_strcmp(fractal->fractal_name, "Julia") == 0)
		iter = julia_iter(c, fractal->c);
	else if (ft_strcmp(fractal->fractal_name, "BurningShip") == 0)
		iter = burning_ship(c, z);
	return (iter);
}

// void	set_mlx(t_fractal fractal)
// {
// }

int	main(int argc, char **argv)
{
	t_fractal	fractal;

	handle_errors(argc, argv);
	fractal.mlx = mlx_init();
	if (fractal.mlx == NULL)
		proper_exit(2);
	fractal.win = mlx_new_window(fractal.mlx, WIDTH, HEIGHT, "Fractal Window");
	if (fractal.win == NULL)
		proper_exit(3);
	fractal.img = mlx_new_image(fractal.mlx, WIDTH, HEIGHT);
	if (fractal.img == NULL)
		proper_exit(4);
	fractal.data_addr = mlx_get_data_addr(fractal.img, &fractal.bpp, \
										&fractal.size_line, &fractal.endian);
	fractal.zoom = 1.0;
	fractal.offset_x = 0.0;
	fractal.offset_y = 0.0;
	fractal.c.r = 0.8;
	fractal.c.i = 0.1;
	fractal.fractal_name = argv[1];
	// set_mlx(fractal);
	draw_fractal(&fractal);
	mlx_put_image_to_window(fractal.mlx, fractal.win, fractal.img, 0, 0);
	mlx_hook(fractal.win, 17, 0, handle_window_close, &fractal);
	mlx_hook(fractal.win, 4, 0, handle_mouse_wheel, &fractal);
	mlx_hook(fractal.win, 6, 0, handle_mouse_movement, &fractal);
	mlx_hook(fractal.win, 3, 0, handle_key_press, &fractal);
	mlx_hook(fractal.win, 2, 0, handle_arrow_keys, &fractal);
	mlx_loop(fractal.mlx);
	return (0);
}

// more protections for windows and images and other functions that return NULL;
//
//
// what to handle in the program ? :
// - the arrows to move around; --DONE--
// - remove the mouse clicking and moving; --DONE--
// - set the Julia set to change when moving the mouse; --DONE--
// - flip the burrningship upside down if possible;
//