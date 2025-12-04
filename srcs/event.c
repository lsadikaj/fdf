/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   event.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsadikaj <lsadikaj@student.42lausanne.ch>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/31 14:49:11 by lsadikaj          #+#    #+#             */
/*   Updated: 2025/12/04 11:27:32 by lsadikaj         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/fdf.h"

void	handle_movement(int keysym, t_fdf *fdf)
{
	if (keysym == KEY_LEFT)
		fdf->offset_x -= 10;
	else if (keysym == KEY_RIGHT)
		fdf->offset_x += 10;
	else if (keysym == KEY_UP)
		fdf->offset_y -= 10;
	else if (keysym == KEY_DOWN)
		fdf->offset_y += 10;
	fdf->needs_redraw = 1;
}

void	handle_transform(int keysym, t_fdf *fdf)
{
	if (keysym == KEY_PLUS)
		fdf->zoom *= 1.1;
	else if (keysym == KEY_MINUS)
		fdf->zoom /= 1.1;
	else if (keysym == KEY_H)
		fdf->hide_lines = !fdf->hide_lines;
	fdf->needs_redraw = 1;
}

void	handle_rotation(int keysym, t_fdf *fdf)
{
	if (keysym == KEY_A)
		fdf->angle_y -= 0.05;
	else if (keysym == KEY_D)
		fdf->angle_y += 0.05;
	else if (keysym == KEY_W)
		fdf->angle_x += 0.05;
	else if (keysym == KEY_S)
		fdf->angle_x -= 0.05;
	fdf->needs_redraw = 1;
}

void	handle_altitude(int keysym, t_fdf *fdf)
{
	float	step;

	step = 0.1;
	if (fdf->projection_mode == PROJ_SPHERE)
		step = 0.02;
	if (keysym == KEY_PAGEUP)
		fdf->altitude += step;
	else if (keysym == KEY_PAGEDOWN)
		fdf->altitude -= step;
	fdf->needs_redraw = 1;
}

void	handle_color_palette(int keysym, t_fdf *fdf)
{
	if (keysym == KEY_SPACE)
	{
		fdf->color_palette = (fdf->color_palette + 1) % NUM_PALETTES;
		ft_printf("Color palette changed: %d\n", fdf->color_palette);
		fdf->needs_redraw = 1;
	}
}
