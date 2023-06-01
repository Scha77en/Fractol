/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fractals.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aouhbi <aouhbi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/30 17:21:04 by aouhbi            #+#    #+#             */
/*   Updated: 2023/06/01 15:16:44 by aouhbi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

int	mandelbrot_iter(t_complex c, t_complex z)
{
	int		n;
	double	zr;
	double	zi;

	n = 0;
	while (n < MAX_ITER)
	{
		zr = z.r * z.r - z.i * z.i + c.r;
		zi = 2 * z.r * z.i - c.i;
		z.r = zr;
		z.i = zi;
		if ((z.r * z.r + z.i * z.i) > 4.0)
			break ;
		n++;
	}
	return (n);
}

int	julia_iter(t_complex z, t_complex c)
{
	int		n;
	double	zr;
	double	zi;

	n = 0;
	while (n < MAX_ITER)
	{
		zr = z.r * z.r - z.i * z.i + c.r;
		zi = 2 * z.r * z.i + c.i;
		z.r = zr;
		z.i = zi;
		if ((z.r * z.r + z.i * z.i) > 4.0)
			break ;
		n++;
	}
	return (n);
}

int	burning_ship(t_complex c, t_complex z)
{
	int		n;
	double	zr;
	double	zi;

	n = 0;
	while (n < MAX_ITER)
	{
		zr = z.r * z.r - z.i * z.i + c.r;
		zi = fabs(2 * z.r * z.i) - c.i;
		z.r = zr;
		z.i = zi;
		if ((z.r * z.r + z.i * z.i) > 4.0)
			break ;
		n++;
	}
	return (n);
}
