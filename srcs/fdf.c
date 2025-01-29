/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsadikaj <lsadikaj@student.42lausanne.ch>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/29 11:47:03 by lsadikaj          #+#    #+#             */
/*   Updated: 2025/01/29 13:40:31 by lsadikaj         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

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
	parse_map(argv[1], &fdf);
	draw_map(&fdf);
	mlx_loop(fdf.mlx);
	return (0);
}