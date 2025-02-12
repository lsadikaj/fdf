/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   projection_utils.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsadikaj <lsadikaj@student.42lausanne.ch>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/11 18:19:28 by lsadikaj          #+#    #+#             */
/*   Updated: 2025/02/12 13:38:12 by lsadikaj         ###   ########.fr       */
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

void	apply_spherical(t_fdf *fdf, t_point *p, int x, int y)
{
	float	lat;
	float	lon;

	lat = (y / (float)fdf->height) * M_PI - M_PI / 2;
	lon = (x / (float)fdf->width) * 2 * M_PI - M_PI;
	p->x = fdf->zoom * cos(lat) * cos(lon);
	p->y = fdf->zoom * cos(lat) * sin(lon);
	p->z = fdf->zoom * sin(lat) * (fdf->altitude + 0.5);
}

void	apply_rotation(t_fdf *fdf, t_point *p)
{
	float	prev[3];

	// Rotation X (W/S)
	prev[1] = p->y;
	prev[2] = p->z;
	p->y = prev[1] * cos(fdf->angle_x) - prev[2] * sin(fdf->angle_x);
	p->z = prev[1] * sin(fdf->angle_x) + prev[2] * cos(fdf->angle_x);

	// Rotation Y (A/D)
	prev[0] = p->x;
	prev[2] = p->z;
	p->x = prev[0] * cos(fdf->angle_y) + prev[2] * sin(fdf->angle_y);
	p->z = -prev[0] * sin(fdf->angle_y) + prev[2] * cos(fdf->angle_y);
}

void	apply_projection(t_fdf *fdf, t_point *p, int x, int y)
{
	if (fdf->projection_mode == PROJ_ISO)
		apply_isometric(&p->x, &p->y, p->z);
	else if (fdf->projection_mode == PROJ_SPHERE)
		apply_spherical(fdf, p, x, y);
}
