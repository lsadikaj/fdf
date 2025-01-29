/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsadikaj <lsadikaj@student.42lausanne.ch>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/29 11:42:30 by lsadikaj          #+#    #+#             */
/*   Updated: 2025/01/29 18:58:55 by lsadikaj         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FDF_H
# define FDF_H

# include <stdlib.h>
# include <unistd.h>
# include <fcntl.h>
# include <math.h>
# include <X11/X.h>
# include <X11/keysym.h>
# include "mlx.h"
# include "../libft/libft.h"
# include "../libft/ft_printf/ft_printf.h"
# include "../libft/get_next_line/get_next_line.h"

typedef struct s_point
{
	int	x;
	int	y;
	int	z;
	int	color;
}	t_point;

typedef struct s_fdf
{
	void	*mlx;
	void	*win;
	void	*img;
	int		**map;
	int		width;
	int		height;
	int		win_width;
	int		win_height;
}	t_fdf;

// Parsing
void	parse_map(char *filename, t_fdf *fdf);
int		count_words(char *line, char delimiter);

// Drawing
void	draw_map(t_fdf *fdf);
void	draw_line(t_fdf *fdf, t_point p1, t_point p2);
void	get_scaled_point(t_fdf *fdf, t_point *p, int x, int y);
void	draw_horizontal(t_fdf *fdf, int x, int y);
void	draw_vertical(t_fdf *fdf, int x, int y);

// Hooks
int		key_hook(int keycode, void *param);
int		close_window(void *param);
int		resize_hook(void *param);

#endif