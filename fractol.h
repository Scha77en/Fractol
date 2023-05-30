/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fractol.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aouhbi <aouhbi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/27 22:37:28 by aouhbi            #+#    #+#             */
/*   Updated: 2023/05/30 13:59:41 by aouhbi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FRACTOL_H
# define FRACTOL_H

# include "mlx.h"
# include <math.h>
# include <stdlib.h>
# include <unistd.h>
# include <string.h>
# include <fcntl.h>

# define WIDTH 800
# define HEIGHT 600
# define ZOOM_FACTOR 1.1
# define MAX_ITER 100
# define COLOR_OFFSET 20

typedef struct s_fractal
{
	void	*mlx;
	void	*win;
	void	*img;
	char	*data_addr;
	int		bpp;
	int		size_line;
	int		endian;
	double	zoom;
	double	offset_x;
	double	offset_y;
	char	*fractal_name;
}	t_fractal;

typedef struct s_complex
{
	double	r;
	double	i;
}	t_complex;

#endif