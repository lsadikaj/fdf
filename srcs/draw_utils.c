/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsadikaj <lsadikaj@student.42lausanne.ch>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/29 16:36:34 by lsadikaj          #+#    #+#             */
/*   Updated: 2025/02/12 13:44:59 by lsadikaj         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/fdf.h"

void	put_pixel(t_fdf *fdf, int x, int y, int color)
{
	char	*dst;

	if (x >= 0 && x < 1920 && y >= 0 && y < 1080)
	{
		dst = fdf->img.addr + (y * fdf->img.line_len + x * (fdf->img.bpp / 8));
		*(unsigned int *)dst = color;
	}
}

void	get_scaled_point(t_fdf *fdf, t_point *p, int x, int y)
{
	float	scale;
	int		center_x;
	int		center_y;

	scale = fdf->zoom;
	center_x = (1920 - 200) / 2;
	center_y = 1080 / 2;
	p->x = (x - fdf->width / 2) * scale;
	p->y = (y - fdf->height / 2) * scale;
	p->z *= (scale / 5) * fdf->altitude;

	if (fdf->projection_mode == PROJ_SPHERE)
	{
		apply_spherical(fdf, p, x, y);
		apply_rotation(fdf, p);
	}
	else
	{
		apply_rotation(fdf, p);
		apply_isometric(&p->x, &p->y, p->z);
	}
	p->x += fdf->offset_x + center_x + 200;
	p->y += fdf->offset_y + center_y;
}

void	draw_line(t_fdf *fdf, t_point p1, t_point p2)
{
	int		dx;
	int		dy;
	int		steps;
	float	x_inc;
	float	y_inc;
	float	percentage;
	float	x;
	float	y;

	dx = p2.x - p1.x;
	dy = p2.y - p1.y;
	if (abs(dx) > abs(dy))
		steps = abs(dx);
	else
		steps = abs(dy);
	x_inc = dx / (float)steps;
	y_inc = dy / (float)steps;
	x = p1.x;
	y = p1.y;
	while (steps--)
	{
		put_pixel(fdf, x, y, gradient_color(p1, p2, percentage));
		x += x_inc;
		y += y_inc;
		percentage += (1.0 / steps);
	}
}

void	draw_horizontal(t_fdf *fdf, int x, int y)
{
	t_point	p1;
	t_point	p2;

	p1.z = fdf->map[y][x];
	p1.color = get_color(x, y, p1.z, fdf);
	get_scaled_point(fdf, &p1, x, y);
	p2.z = fdf->map[y][x + 1];
	p2.color = get_color(x + 1, y, p2.z, fdf);
	get_scaled_point(fdf, &p2, x + 1, y);
	draw_line(fdf, p1, p2);
}

void	draw_vertical(t_fdf *fdf, int x, int y)
{
	t_point	p1;
	t_point	p2;

	p1.z = fdf->map[y][x];
	p1.color = get_color(x, y, p1.z, fdf);
	get_scaled_point(fdf, &p1, x, y);
	p2.z = fdf->map[y + 1][x];
	p2.color = get_color(x, y + 1, p2.z, fdf);
	get_scaled_point(fdf, &p2, x, y + 1);
	draw_line(fdf, p1, p2);
}
