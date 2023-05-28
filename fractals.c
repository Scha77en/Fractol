/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fractals.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aouhbi <aouhbi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/25 22:39:16 by aouhbi            #+#    #+#             */
/*   Updated: 2023/05/28 02:11:29 by aouhbi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mlx.h"
#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <string.h>

#define WIDTH 800
#define HEIGHT 600
#define ZOOM_FACTOR 1.1
#define MAX_ITER 100
#define COLOR_OFFSET 20

typedef struct s_complex
{
	double r;
	double i;
} t_complex;

typedef struct s_fractal
{
	void *mlx;
	void *win;
	void *img;
	char *data_addr;
	int bpp;
	int size_line;
	int endian;
	double zoom;
	double offset_x;
	double offset_y;
	char *fractal_name;
} t_fractal;

int mandelbrot_iter(t_complex c, t_complex z)
{
	int n = 0;
	while (n < MAX_ITER)
	{
		double zr = z.r * z.r - z.i * z.i + c.r;
		double zi = 2 * z.r * z.i + c.i;
		z.r = zr;
		z.i = zi;
		if ((z.r * z.r + z.i * z.i) > 4.0)
			break;
		n++;
	}
	return n;
}

int julia_iter(t_complex z, t_complex c)
{
	int n = 0;
	while (n < MAX_ITER)
	{
		double zr = z.r * z.r - z.i * z.i + c.r;
		double zi = 2 * z.r * z.i + c.i;
		z.r = zr;
		z.i = zi;
		if ((z.r * z.r + z.i * z.i) > 4.0)
			break;
		n++;
	}
	return n;
}

int get_color(int n)
{
	int red = sin(0.1 * n + 0) * 127 + 128;
	int green = sin(0.1 * n + 2) * 127 + 128;
	int blue = sin(0.1 * n + 4) * 127 + 128;
	return (red << 16) + (green << 8) + blue;
}

void display_fractals_list(void)
{
	printf("Available fractals:\n");
	printf("- Mandelbrot\n");
	printf("- Julia\n");
	printf("Usage: ./program_name <binary_file_name> <fractal_name>\n");
}

int draw_fractal(t_fractal *fractal)
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
				iter = julia_iter(c, z);
			else
			{
				printf("Invalid fractal name!\n");
				display_fractals_list();
				return 1;
			}

			color = get_color(iter + COLOR_OFFSET);
			fractal->data_addr[(x * fractal->bpp / 8) + (y * fractal->size_line)] = color & 0xFF;           // blue channel
			fractal->data_addr[(x * fractal->bpp / 8) + (y * fractal->size_line) + 1] = (color >> 8) & 0xFF;  // green channel
			fractal->data_addr[(x * fractal->bpp / 8) + (y * fractal->size_line) + 2] = (color >> 16) & 0xFF; // red channel
			x++;
		}
		y++;
	}
	return 0;
}

int handle_key_press(int keycode, t_fractal *fractal)
{
	if (keycode == 53) // ESC key
	{
		mlx_destroy_image(fractal->mlx, fractal->img);
		mlx_destroy_window(fractal->mlx, fractal->win);
		exit(0);
	}
	return 0;
}

int handle_window_close(t_fractal *fractal)
{
	mlx_destroy_image(fractal->mlx, fractal->img);
	mlx_destroy_window(fractal->mlx, fractal->win);
	exit(0);
	return 0;
}

int handle_mouse_wheel(int button, int x, int y, t_fractal *fractal)
{
	if (button == 4) // Mouse wheel up
		fractal->zoom *= ZOOM_FACTOR;
	else if (button == 5) // Mouse wheel down
		fractal->zoom /= ZOOM_FACTOR;

	// fractal->offset_x = (x - WIDTH / 2) / (0.5 * fractal->zoom * WIDTH) + fractal->offset_x;
	// fractal->offset_y = (y - HEIGHT / 2) / (0.5 * fractal->zoom * HEIGHT) + fractal->offset_y;

	draw_fractal(fractal);
	mlx_put_image_to_window(fractal->mlx, fractal->win, fractal->img, 0, 0);
	return 0;
}

int main(int argc, char *argv[])
{
	if (argc != 3)
	{
		printf("Usage: %s <binary_file_name> <fractal_name>\n", argv[0]);
		display_fractals_list();
		return 1;
	}

	t_fractal fractal;

	fractal.mlx = mlx_init();
	fractal.win = mlx_new_window(fractal.mlx, WIDTH, HEIGHT, "Fractal Window");
	fractal.img = mlx_new_image(fractal.mlx, WIDTH, HEIGHT);
	fractal.data_addr = mlx_get_data_addr(fractal.img, &fractal.bpp, &fractal.size_line, &fractal.endian);
	fractal.zoom = 1.0;
	fractal.offset_x = 0.0;
	fractal.offset_y = 0.0;
	fractal.fractal_name = argv[2];

	draw_fractal(&fractal);
	mlx_put_image_to_window(fractal.mlx, fractal.win, fractal.img, 0, 0);
	mlx_hook(fractal.win, 2, 0, handle_key_press, &fractal);
	mlx_hook(fractal.win, 17, 0, handle_window_close, &fractal);
	mlx_hook(fractal.win, 4, 0, handle_mouse_wheel, &fractal);
	mlx_loop(fractal.mlx);

	return 0;
}


// cc -I /usr/local/include fractol.c -L /usr/local/lib -lmlx -framework OpenGL -framework AppKit

// void	ft_putchar(char c)
// {
// 	printf("KEY\n");
// }

// int	deal_key(int key, void *param)
// {
// 	ft_putchar('X');
// 	return (0);
// }

// int	main(void)
// {
// 	void	*mlx_ptr;
// 	void	*win_ptr;

// 	mlx_ptr = mlx_init();
// 	mlx_new_window(mlx_ptr, 500, 500, "Fractal");
// 	mlx_key_hook(win_ptr, deal_key, (void *)0);
// 	mlx_loop(mlx_ptr);
// }
