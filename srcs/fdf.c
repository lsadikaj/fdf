/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsadikaj <lsadikaj@student.42lausanne.ch>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/29 11:47:03 by lsadikaj          #+#    #+#             */
/*   Updated: 2025/02/05 14:32:57 by lsadikaj         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/fdf.h"

int	close_window(void *param)
{
	t_fdf	*fdf;

	fdf = (t_fdf *)param;
	ft_printf("Window closed.\n");
	mlx_destroy_window(fdf->mlx, fdf->win);
	exit(0);
	return (0);
}

int	key_hook(int keycode, void *param)
{
	t_fdf	*fdf;

	fdf = (t_fdf *)param;
	ft_printf("Key released (keycode): %d\n", keycode);

	if (keycode == XK_Escape)
		close_window(fdf);
	handle_movement(keycode, fdf);
	handle_transform(keycode, fdf);
	handle_rotation(keycode, fdf);
	handle_altitude(keycode, fdf);
	handle_color_palette(keycode, fdf);
	mlx_destroy_image(fdf->mlx, fdf->img.img);
	fdf->img.img = mlx_new_image(fdf->mlx, 1920, 1080);
	fdf->img.addr = mlx_get_data_addr(fdf->img.img, &fdf->img.bpp, &fdf->img.line_len, &fdf->img.endian);
	draw_map(fdf);
	return (0);
}

static void	init_fdf(t_fdf *fdf)
{
	fdf->zoom = 30;
	fdf->altitude = 1;
	fdf->angle_x = 0;
	fdf->angle_y = 0;
	fdf->offset_x = 140;
	fdf->offset_y = -549;
	fdf->hide_lines = 0;
	fdf->color_palette = 0;
}

int	main(int argc, char **argv)
{
	t_fdf	fdf;

	if (argc != 2)
	{
		write(2, "Usage: ./fdf <map.fdf>\n", 23);
		return (1);
	}
	fdf.mlx = mlx_init();
	fdf.win = mlx_new_window(fdf.mlx, 1920, 1080, "Fil de Fer");
	fdf.img.img = mlx_new_image(fdf.mlx, 1920, 1080);
	fdf.img.addr = mlx_get_data_addr(fdf.img.img, &fdf.img.bpp,
			&fdf.img.line_len, &fdf.img.endian);
	init_fdf(&fdf);
	mlx_hook(fdf.win, 2, 1L << 0, key_hook, (void *)&fdf);
	mlx_hook(fdf.win, 17, 0, close_window, (void *)&fdf);
	parse_map(argv[1], &fdf);
	draw_map(&fdf);
	mlx_loop(fdf.mlx);
	return (0);
}
