/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   proper_exit.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aouhbi <aouhbi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/30 17:26:43 by aouhbi            #+#    #+#             */
/*   Updated: 2023/06/01 16:35:20 by aouhbi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

void	proper_exit(int v)
{
	if (v == 1)
	{
		write(1, "Usage: ./fractol <the fractal>\n", 32);
		write(1, "available fractals:\n", 21);
		write(1, "\tMandelbrot\n", 13);
		write(1, "\tJulia\n", 8);
		write(1, "\tBurningShip\n", 14);
	}
	else if (v == 2)
		write(2, "Failed to set up connection to the graphical system!\n", 54);
	else if (v == 3)
		write(2, "Failed to create new window\n", 29);
	else if (v == 4)
		write(2, "Failed to create new image\n", 29);
	exit(v);
}

void	handle_errors(int argc, char **argv)
{
	if (argc != 2 || (ft_strcmp(argv[1], "Mandelbrot")
			&& ft_strcmp(argv[1], "Julia")
			&& ft_strcmp(argv[1], "BurningShip")))
		proper_exit(1);
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
