/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   event.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsadikaj <lsadikaj@student.42lausanne.ch>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/31 14:49:11 by lsadikaj          #+#    #+#             */
/*   Updated: 2025/02/12 13:43:33 by lsadikaj         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/fdf.h"

void	handle_movement(int keysym, t_fdf *fdf)
{
	if (keysym == XK_Left)
		fdf->offset_x -= 10;
	else if (keysym == XK_Right)
		fdf->offset_x += 10;
	else if (keysym == XK_Up)
		fdf->offset_y -= 10;
	else if (keysym == XK_Down)
		fdf->offset_y += 10;
}

void	handle_transform(int keysym, t_fdf *fdf)
{
	if (keysym == XK_plus || keysym == XK_KP_Add)
			fdf->zoom *= 1.1;
	else if (keysym == XK_minus || keysym == XK_KP_Subtract)
			fdf->zoom /= 1.1;
	else if (keysym == XK_h)
		fdf->hide_lines = !fdf->hide_lines;
}

void	handle_rotation(int keysym, t_fdf *fdf)
{
	if (keysym == XK_a)
		fdf->angle_y -= 0.05;
	else if (keysym == XK_d)
		fdf->angle_y += 0.05;
	else if (keysym == XK_w)
		fdf->angle_x += 0.05;
	else if (keysym == XK_s)
		fdf->angle_x -= 0.05;
	fdf->needs_redraw = 1;
}

void	handle_altitude(int keysym, t_fdf *fdf)
{
	if (keysym == XK_Page_Up)
		fdf->altitude += 0.02;
	else if (keysym == XK_Page_Down)
		fdf->altitude -= 0.02;
	fdf->needs_redraw = 1;
}

void	handle_color_palette(int keysym, t_fdf *fdf)
{
	if (keysym == XK_space)
	{
		fdf->color_palette = (fdf->color_palette + 1) % NUM_PALETTES;
		ft_printf("Color palette changed: %d\n", fdf->color_palette);
		fdf->needs_redraw = 1;
	}
}