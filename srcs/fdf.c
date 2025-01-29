/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsadikaj <lsadikaj@student.42lausanne.ch>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/29 11:47:03 by lsadikaj          #+#    #+#             */
/*   Updated: 2025/01/29 19:12:23 by lsadikaj         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/fdf.h"

int	close_window(void *param)
{
	t_fdf	*fdf;

	fdf = (t_fdf *)param;
	mlx_destroy_window(fdf->mlx, fdf->win);
	ft_printf("Window closed.\n");
	exit(0);
	return (0);
}

int	key_hook(int keycode, void *param)
{
	t_fdf	*fdf;

	fdf = (t_fdf *)param;
	ft_printf("Key pressed: %d\n", keycode);
	if (keycode == XK_Escape)
		close_window(fdf);
	return (0);
}

int	resize_hook(void *param)
{
	t_fdf	*fdf;
	int		new_width;
	int		new_height;

	fdf = (t_fdf *)param;
	new_width = 1920;
	new_height = 1080;
	if (new_width != fdf->win_width || new_height != fdf->win_height)
	{
		fdf->win_width = new_width;
		fdf->win_height = new_height;
		mlx_clear_window(fdf->mlx, fdf->win);
		draw_map(fdf);
	}
	return (0);
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
	fdf.win_width = 1920;
	fdf.win_height = 1080;
	mlx_hook(fdf.win, 17, 0, close_window, (void *)&fdf);
	mlx_hook(fdf.win, 2, 1L << 0, key_hook, (void *)&fdf);
	mlx_loop_hook(fdf.mlx, resize_hook, (void *)&fdf);
	parse_map(argv[1], &fdf);
	draw_map(&fdf);
	mlx_loop(fdf.mlx);
	return (0);
}
