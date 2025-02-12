/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsadikaj <lsadikaj@student.42lausanne.ch>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/29 11:42:30 by lsadikaj          #+#    #+#             */
/*   Updated: 2025/02/12 13:32:17 by lsadikaj         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FDF_H
# define FDF_H

# include <stdlib.h>
# include <unistd.h>
# include <fcntl.h>
# include <math.h>
# include <X11/X.h>
# include <X11/Xlib.h>
# include <X11/keysym.h>
# include "mlx.h"
# include "../libft/libft.h"
# include "../libft/ft_printf/ft_printf.h"
# include "../libft/get_next_line/get_next_line.h"

# define NUM_PALETTES 3

typedef enum e_projection
{
	PROJ_ISO,
	PROJ_SPHERE
}	t_projection;

typedef struct s_img
{
	void	*img;
	char	*addr;
	int		bpp;
	int		line_len;
	int		endian;
}	t_img;

typedef struct s_point
{
	int	x;
	int	y;
	int	z;
	int	color;
}	t_point;

typedef struct s_fdf
{
	void			*mlx;
	void			*win;
	t_img			img;
	int				**map;
	int				**colors;
	int				width;
	int				height;
	int				offset_x;
	int				offset_y;
	float			zoom;
	float			altitude;
	float			angle_x;
	float			angle_y;
	int				hide_lines;
	int				color_palette;
	int				needs_redraw;
	t_projection	projection_mode;
}	t_fdf;

// Parsing
void	parse_map(char *filename, t_fdf *fdf);
int		count_words(char *line, char delimiter);
void	free_map(int **map, int allocated_rows);
int		**allocate_map(int width, int height);
int		**allocate_colors(int width, int height);
int		ft_atoi_base(char *str, char *base);
void	fill_map_row(int **map, int **colors, char *line, int row, int width);
void	parse_point(char *str, int *z, int *color);

// Drawing
void	apply_isometric(int *x, int *y, int z);
void	apply_spherical(t_fdf *fdf, t_point *p, int x, int y);
void	apply_rotation(t_fdf *fdf, t_point *p);
void	apply_projection(t_fdf *fdf, t_point *p, int x, int y);
void	draw_map(t_fdf *fdf);
void	draw_banner(t_fdf *fdf);
void	draw_line(t_fdf *fdf, t_point p1, t_point p2);
void	put_pixel(t_fdf *fdf, int x, int y, int color);
void	get_scaled_point(t_fdf *fdf, t_point *p, int x, int y);
void	draw_horizontal(t_fdf *fdf, int x, int y);
void	draw_vertical(t_fdf *fdf, int x, int y);

// Hooks
int		key_hook(int keycode, void *param);
int		close_window(void *param);
int		render_frame(void *param);
void	handle_movement(int keysym, t_fdf *fdf);
void	handle_transform(int keysym, t_fdf *fdf);
void	handle_rotation(int keysym, t_fdf *fdf);
void	handle_altitude(int keysym, t_fdf *fdf);
void	handle_projection(int keysym, t_fdf *fdf);

// Colors
int		get_color(int x, int y, int z, t_fdf *fdf);
int		gradient_color(t_point p1, t_point p2, float percentage);
void	handle_color_palette(int keysym, t_fdf *fdf);

#endif