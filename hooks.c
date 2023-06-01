/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hooks.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aouhbi <aouhbi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/30 17:23:03 by aouhbi            #+#    #+#             */
/*   Updated: 2023/06/01 16:25:23 by aouhbi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

int	handle_key_press(int keycode, t_fractal *fractal)
{
	if (keycode == 53)
	{
		mlx_destroy_image(fractal->mlx, fractal->img);
		mlx_destroy_window(fractal->mlx, fractal->win);
		exit(0);
	}
	return (0);
}

int	handle_window_close(t_fractal *fractal)
{
	mlx_destroy_image(fractal->mlx, fractal->img);
	mlx_destroy_window(fractal->mlx, fractal->win);
	exit(0);
	return (0);
}

int	handle_arrow_keys(int keycode, t_fractal *fractal)
{
	if (keycode == 123)
		fractal->offset_x -= 0.1 / fractal->zoom;
	else if (keycode == 124)
		fractal->offset_x += 0.1 / fractal->zoom;
	else if (keycode == 125)
		fractal->offset_y += 0.1 / fractal->zoom;
	else if (keycode == 126)
		fractal->offset_y -= 0.1 / fractal->zoom;
	draw_fractal(fractal);
	mlx_put_image_to_window(fractal->mlx, fractal->win, fractal->img, 0, 0);
	return (0);
}

int	handle_mouse_wheel(int button, int x, int y, t_fractal *fractal)
{
	if (button == 4)
	{
		fractal->zoom *= ZOOM_FACTOR;
		fractal->offset_x = (x - WIDTH / 2) / (0.5 * fractal->zoom * WIDTH) \
		+ fractal->offset_x;
		fractal->offset_y = (y - HEIGHT / 2) / (0.5 * fractal->zoom * HEIGHT) \
		+ fractal->offset_y;
		draw_fractal(fractal);
		mlx_put_image_to_window(fractal->mlx, fractal->win, fractal->img, 0, 0);
	}
	else if (button == 5)
	{
		fractal->zoom /= ZOOM_FACTOR;
		fractal->offset_x = (x - WIDTH / 2) / (0.5 * fractal->zoom * WIDTH) \
							+ fractal->offset_x;
		fractal->offset_y = (y - HEIGHT / 2) / (0.5 * fractal->zoom * HEIGHT) \
							+ fractal->offset_y;
		draw_fractal(fractal);
		mlx_put_image_to_window(fractal->mlx, fractal->win, fractal->img, 0, 0);
	}
	return (0);
}

int	handle_mouse_movement(int x, int y, t_fractal *fractal)
{
	if (ft_strcmp(fractal->fractal_name, "Julia") == 0)
	{
		fractal->c.r = (x - WIDTH / 2.0) / (0.5 * fractal->zoom * WIDTH);
		fractal->c.i = (y - HEIGHT / 2.0) / (0.5 * fractal->zoom * HEIGHT);
		draw_fractal(fractal);
		mlx_put_image_to_window(fractal->mlx, fractal->win, fractal->img, 0, 0);
	}
	return (0);
}
