/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_map.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsadikaj <lsadikaj@student.42lausanne.ch>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/29 15:16:37 by lsadikaj          #+#    #+#             */
/*   Updated: 2025/02/12 13:44:21 by lsadikaj         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/fdf.h"

void	draw_banner(t_fdf *fdf)
{
	int	y_offset;

	y_offset = 50; 

	mlx_string_put(fdf->mlx, fdf->win, 40, y_offset, 0xFFFFFF, "    FDF Project   ");
	y_offset += 30;
	mlx_string_put(fdf->mlx, fdf->win, 40, y_offset, 0xFFFFFF, "-------------------");
	y_offset += 30;
	mlx_string_put(fdf->mlx, fdf->win, 40, y_offset, 0xFFFFFF, " Zoom: +/- ");
	y_offset += 30;
	mlx_string_put(fdf->mlx, fdf->win, 40, y_offset, 0xFFFFFF, " Rotate: W/A/S/D ");
	y_offset += 30;
	mlx_string_put(fdf->mlx, fdf->win, 40, y_offset, 0xFFFFFF, " Move: Arrows");
	y_offset += 30;
	mlx_string_put(fdf->mlx, fdf->win, 40, y_offset, 0xFFFFFF, " Altitude: PgUp/PgDn");
	y_offset += 30;
	mlx_string_put(fdf->mlx, fdf->win, 40, y_offset, 0xFFFFFF, " Color: Space");
	y_offset += 30;
	mlx_string_put(fdf->mlx, fdf->win, 40, y_offset, 0xFFFFFF, " Hide lines: H ");
	y_offset += 30;
	mlx_string_put(fdf->mlx, fdf->win, 40, y_offset, 0xFFFFFF, " Projection Mode: P ");
	y_offset += 30;
	mlx_string_put(fdf->mlx, fdf->win, 40, y_offset, 0xFFFFFF, "-------------------");
}

void	draw_map(t_fdf *fdf)
{
	int		x;
	int		y;
	t_point	p;

	mlx_clear_window(fdf->mlx, fdf->win);
	y = 0;
	while (y < fdf->height)
	{
		x = 0;
		while (x < fdf->width)
		{
			p.z = fdf->map[y][x];  
			p.color = get_color(x, y, p.z, fdf);
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
	draw_banner(fdf);
}
