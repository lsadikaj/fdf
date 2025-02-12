/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsadikaj <lsadikaj@student.42lausanne.ch>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/04 14:30:19 by lsadikaj          #+#    #+#             */
/*   Updated: 2025/02/12 13:54:03 by lsadikaj         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/fdf.h"

int	gradient_color(t_point p1, t_point p2, float percentage)
{
	int	red;
	int	green;
	int	blue;

	if (percentage < 0.0)
		percentage = 0.0;
	if (percentage > 1.0)
		percentage = 1.0;
	red = (int)((1.0 - percentage) * ((p1.color >> 16) & 0xFF) +
			percentage * ((p2.color >> 16) & 0xFF));
	green = (int)((1.0 - percentage) * ((p1.color >> 8) & 0xFF) +
			percentage * ((p2.color >> 8) & 0xFF));
	blue = (int)((1.0 - percentage) * (p1.color & 0xFF) +
			percentage * (p2.color & 0xFF));
			
	return ((red << 16) | (green << 8) | blue);
}

int	get_color(int x, int y, int z, t_fdf *fdf)
{
	static int	palettes[NUM_PALETTES][3] = {
		{0xFFFFFF, 0xFFFFFF, 0xFFFFFF},
		{0xFFFFFF, 0xFFA500, 0x0000FF},
		{0xFFFFFF, 0x00FF00, 0xFF0000}
	};
	int	*selected_palette;

	if (fdf->colors[y][x] != -1)
		return (fdf->colors[y][x]);
	selected_palette = palettes[fdf->color_palette];
	if (z > 0)
		return (selected_palette[1]);
	else if (z < 0)
		return (selected_palette[2]);
	return (selected_palette[0]);
}
