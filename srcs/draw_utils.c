/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsadikaj <lsadikaj@student.42lausanne.ch>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/29 16:36:34 by lsadikaj          #+#    #+#             */
/*   Updated: 2025/01/29 18:57:39 by lsadikaj         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/fdf.h"


void	draw_line(t_fdf *fdf, t_point p1, t_point p2)
{
	int		dx;
	int		dy;
	int		steps;
	float	x_inc;
	float	y_inc;
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
		mlx_pixel_put(fdf->mlx, fdf->win, x, y, p1.color);
		x += x_inc;
		y += y_inc;
	}
}

void	get_scaled_point(t_fdf *fdf, t_point *p, int x, int y)
{
	float	scale_x;
	float	scale_y;
	float	scale;
	int		offset_x;
	int		offset_y;

	scale_x = fdf->win_width / (float)fdf->width;
	scale_y = fdf->win_height / (float)fdf->height;
	if (scale_x < scale_y)
		scale = scale_x;
	else
		scale = scale_y;
	if (scale < 1)
		scale = 1;
	offset_x = (fdf->win_width - (fdf->width * scale)) / 2;
	offset_y = (fdf->win_height - (fdf->height * scale)) / 2;
	p->x = x * scale + offset_x;
	p->y = y * scale -(p->z * (scale / 5)) + offset_y;
}

void	draw_horizontal(t_fdf *fdf, int x, int y)
{
	t_point	p1;
	t_point	p2;

	p1.z = fdf->map[y][x];
	p1.color = 0xFFFFFF;
	get_scaled_point(fdf, &p1, x, y);
	p2.z = fdf->map[y][x + 1];
	p2.color = 0xFFFFFF;
	get_scaled_point(fdf, &p2, x + 1, y);
	draw_line(fdf, p1, p2);
}

void	draw_vertical(t_fdf *fdf, int x, int y)
{
	t_point	p1;
	t_point	p2;

	p1.z = fdf->map[y][x];
	p1.color = 0xFFFFFF;
	get_scaled_point(fdf, &p1, x, y);
	p2.z = fdf->map[y + 1][x];
	p2.color = 0xFFFFFF;
	get_scaled_point(fdf, &p2, x, y + 1);
	draw_line(fdf, p1, p2);
}
