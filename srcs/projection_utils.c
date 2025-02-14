/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   projection_utils.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsadikaj <lsadikaj@student.42lausanne.ch>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/11 18:19:28 by lsadikaj          #+#    #+#             */
/*   Updated: 2025/02/14 14:54:55 by lsadikaj         ###   ########.fr       */
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
	float	base_radius;
	float	altitude_effect;

	// Calcul latitude et longitude
	lat = ((float)y / (float)(fdf->height - 1)) * M_PI - M_PI / 2;
	lon = ((float)x / (float)(fdf->width - 1)) * 2 * M_PI - M_PI;

	// Base du rayon de la sphère
	base_radius = fdf->zoom * 0.4;

	// Appliquer l'altitude en prenant en compte la valeur de l'utilisateur
	altitude_effect = (p->z / 10.0f) * (fdf->altitude * 0.5);

	// Éviter une altitude trop forte qui déforme tout
	if (altitude_effect > base_radius * 0.5)
		altitude_effect = base_radius * 0.5;
	if (altitude_effect < -base_radius * 0.5)
		altitude_effect = -base_radius * 0.5;

	// Conversion en sphérique
	p->x = (base_radius + altitude_effect) * cos(lat) * cos(lon);
	p->y = (base_radius + altitude_effect) * cos(lat) * sin(lon);
	p->z = (base_radius + altitude_effect) * sin(lat);
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
