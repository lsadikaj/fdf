/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_banner.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsadikaj <lsadikaj@student.42lausanne.ch>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/19 12:48:17 by lsadikaj          #+#    #+#             */
/*   Updated: 2025/02/19 14:14:01 by lsadikaj         ###   ########.fr       */
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
