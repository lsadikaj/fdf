/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_map.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsadikaj <lsadikaj@student.42lausanne.ch>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/29 15:16:37 by lsadikaj          #+#    #+#             */
/*   Updated: 2025/02/18 12:28:43 by lsadikaj         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/fdf.h"

static void	draw_banner_line(t_fdf *fdf, int *y, char *text)
{
	mlx_string_put(fdf->mlx, fdf->win, 40, *y, 0xFFFFFF, text);
	*y += 30;
}

void	draw_banner(t_fdf *fdf)
{
	int	y;

	y = 50;
	draw_banner_line(fdf, &y, "    FDF Project   ");
	draw_banner_line(fdf, &y, "-------------------");
	draw_banner_line(fdf, &y, " Zoom: +/- ");
	draw_banner_line(fdf, &y, " Rotate: W/A/S/D ");
	draw_banner_line(fdf, &y, " Move: Arrows");
	draw_banner_line(fdf, &y, " Altitude: PgUp/PgDn");
	draw_banner_line(fdf, &y, " Color: Space");
	draw_banner_line(fdf, &y, " Hide lines: H ");
	draw_banner_line(fdf, &y, " Projection Mode: P ");
	draw_banner_line(fdf, &y, "-------------------");
}

static void	init_bres(t_bres *br, t_point p1, t_point p2)
{
	br->dx = p2.x - p1.x;
	if (br->dx < 0)
		br->dx = -br->dx;
	br->dy = p2.y - p1.y;
	if (br->dy < 0)
		br->dy = -br->dy;
	if (p1.x < p2.x)
		br->sx = 1;
	else
		br->sx = -1;
	if (p1.y < p2.y)
		br->sy = 1;
	else
		br->sy = -1;
	br->err = br->dx - br->dy;
	if (br->dx > br->dy)
		br->max_val = br->dx;
	else
		br->max_val = br->dy;
	if (br->max_val == 0)
		br->max_val = 1;
	br->x = p1.x;
	br->y = p1.y;
	br->i = 0;
}

void	draw_line(t_fdf *fdf, t_point p1, t_point p2)
{
	t_bres	br;
	int		e2;
	float	perc;

	init_bres(&br, p1, p2);
	while (1)
	{
		perc = (float)br.i / (float)br.max_val;
		put_pixel(fdf, br.x, br.y, gradient_color(p1, p2, perc));
		if (br.x == p2.x && br.y == p2.y)
			break ;
		e2 = 2 * br.err;
		if (e2 > -br.dy)
		{
			br.err -= br.dy;
			br.x += br.sx;
		}
		if (e2 < br.dx)
		{
			br.err += br.dx;
			br.y += br.sy;
		}
		br.i++;
	}
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
