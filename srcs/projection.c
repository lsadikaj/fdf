/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   projection.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsadikaj <lsadikaj@student.42lausanne.ch>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/11 18:14:08 by lsadikaj          #+#    #+#             */
/*   Updated: 2025/02/14 15:15:36 by lsadikaj         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/fdf.h"

#define DEFAULT_ALTITUDE_SPHERE 0.2
#define DEFAULT_ZOOM_SPHERE 300

void	handle_projection(int keysym, t_fdf *fdf)
{
	static float prev_altitude = 1.0;
	static float prev_zoom = 0;

	if (keysym == XK_p)
	{
		if (fdf->projection_mode == PROJ_ISO)
		{
			prev_altitude = fdf->altitude;
			prev_zoom = fdf->zoom;
			fdf->projection_mode = PROJ_SPHERE;
			fdf->zoom = DEFAULT_ZOOM_SPHERE;
			fdf->altitude = prev_altitude * DEFAULT_ALTITUDE_SPHERE;
		}
		else
		{
			fdf->projection_mode = PROJ_ISO;
			if (prev_zoom > 0)
				fdf->zoom = prev_zoom;
			fdf->altitude = prev_altitude;
		}
		fdf->needs_redraw = 1;
	}
}
