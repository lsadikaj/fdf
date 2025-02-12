/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   projection.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsadikaj <lsadikaj@student.42lausanne.ch>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/11 18:14:08 by lsadikaj          #+#    #+#             */
/*   Updated: 2025/02/12 13:29:04 by lsadikaj         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/fdf.h"

void	handle_projection(int keysym, t_fdf *fdf)
{
	if (keysym == XK_p)
	{
		if (fdf->projection_mode == PROJ_ISO)
			fdf->projection_mode = PROJ_SPHERE;
		else
			fdf->projection_mode = PROJ_ISO;
		ft_printf("Projection mode changed: ");
		if (fdf->projection_mode == PROJ_ISO)
			ft_printf("Isometric\n");
		else
			ft_printf("Spherical\n");
		fdf->needs_redraw = 1;
	}
}
