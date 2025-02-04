/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_map.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsadikaj <lsadikaj@student.42lausanne.ch>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/29 15:16:37 by lsadikaj          #+#    #+#             */
/*   Updated: 2025/02/04 16:41:18 by lsadikaj         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/fdf.h"

void	apply_isometric(int *x, int *y, int z)
{
	int	prev_x;
	int	prev_y;

	prev_x = *x;
	prev_y = *y;
	*x = (prev_x - prev_y) * cos(0.523599);
	*y = (prev_x + prev_y) * sin(0.523599) - z;
}

void	draw_map(t_fdf *fdf)
{
	int	x;
	int	y;
	t_point	p;

	mlx_clear_window(fdf->mlx, fdf->win);
	y = 0;
	while (y < fdf->height)
	{
		x = 0;
		while (x < fdf->width)
		{
			p.z = fdf->map[y][x];
			p.color = get_color(p.z, fdf);
			get_scaled_point(fdf, &p, x, y);
			put_pixel(fdf, p.x, p.y, p.color);
			if (!fdf->hide_lines)
			{
				if (x < fdf->width - 1)
					draw_horizontal(fdf, x, y);
				if (y < fdf->height - 1)
					draw_vertical(fdf, x, y);
			}
			x++;
		}
		y++;
	}
	mlx_put_image_to_window(fdf->mlx, fdf->win, fdf->img.img, 0, 0);
}
