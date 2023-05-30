/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   proper_exit.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aouhbi <aouhbi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/30 17:26:43 by aouhbi            #+#    #+#             */
/*   Updated: 2023/05/30 17:27:11 by aouhbi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

void	proper_exit(int v)
{
	if (v == 1)
	{
		write(2, "Usage: ./fractol <the fractal>\n", 32);
		write(2, "available fractals:\n", 21);
		write(2, "\tMandelbrot\n", 13);
		write(2, "\tJulia\n", 8);
		exit(1);
	}
}

void	handle_errors(int argc, char **argv)
{
	if (argc != 2 || (strcmp(argv[1], "Mandelbrot")
			&& strcmp(argv[1], "Julia")))
		proper_exit(1);
}
