/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fractol.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aouhbi <aouhbi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/27 22:33:53 by aouhbi            #+#    #+#             */
/*   Updated: 2023/05/30 19:31:31 by aouhbi           ###   ########.fr       */
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
	int x;
	int y;
	int iter;
	int color;

	y = 0;
	while (y < HEIGHT)
	{
		x = 0;
		while (x < WIDTH)
		{
			t_complex c;
			t_complex z;

			c.r = (x - WIDTH / 2) / (0.5 * fractal->zoom * WIDTH) + fractal->offset_x;
			c.i = (y - HEIGHT / 2) / (0.5 * fractal->zoom * HEIGHT) + fractal->offset_y;

			z.r = 0.0;
			z.i = 0.0;

			if (strcmp(fractal->fractal_name, "Mandelbrot") == 0)
				iter = mandelbrot_iter(c, z);
			else if (strcmp(fractal->fractal_name, "Julia") == 0)
				iter = julia_iter(c, z, *fractal);
			color = get_color(iter + COLOR_OFFSET);
			fractal->data_addr[(x * fractal->bpp / 8) + (y * fractal->size_line)] = color & 0xFF;           // blue channel
			fractal->data_addr[(x * fractal->bpp / 8) + (y * fractal->size_line) + 1] = (color >> 8) & 0xFF;  // green channel
			fractal->data_addr[(x * fractal->bpp / 8) + (y * fractal->size_line) + 2] = (color >> 16) & 0xFF; // red channel
			x++;
		}
		y++;
	}
}

int	main(int argc, char **argv)
{
	t_fractal	fractal;

	handle_errors(argc, argv);
	fractal.mlx = mlx_init();
	fractal.win = mlx_new_window(fractal.mlx, WIDTH, HEIGHT, "Fractal Window");
	fractal.img = mlx_new_image(fractal.mlx, WIDTH, HEIGHT);
	fractal.data_addr = mlx_get_data_addr(fractal.img, &fractal.bpp, \
										&fractal.size_line, &fractal.endian);
	fractal.zoom = 1.0;
	fractal.offset_x = 0.0;
	fractal.offset_y = 0.0;
	fractal.fractal_name = argv[1];
	draw_fractal(&fractal);
	mlx_put_image_to_window(fractal.mlx, fractal.win, fractal.img, 0, 0);
	mlx_hook(fractal.win, 17, 0, handle_window_close, &fractal);
	mlx_hook(fractal.win, 4, 0, handle_mouse_wheel, &fractal);
	mlx_hook(fractal.win, 6, 0, handle_mouse_movement, &fractal);
	mlx_hook(fractal.win, 3, 0, handle_key_press, &fractal);
	mlx_hook(fractal.win, 2, 1L << 2, handle_arrow_keys, &fractal);
	mlx_loop(fractal.mlx);
	return (0);
}

int	ft_strcmp(char *s1, char *s2)
{
	int		i;

	i = 0;
	while (s1[i] || s2[i])
	{
		if (s1[i] != s2[i])
			return (s1[i] - s2[i]);
		i++;
	}
	return (0);
}

// more protections for windows and images and other functions that return NULL;
//
// what to handle in the program ? :
// - the arrows to move around; --DONE--
// - remove the mouse clicking and moving; --DONE--
// - set the Julia set to change when moving the mouse;
// - flip the burrningship upside down if possible;
//